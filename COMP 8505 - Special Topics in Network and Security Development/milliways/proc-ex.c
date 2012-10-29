
// This program will examine the kernel's live process table in /proc,
// search for a specified process and return its PID

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/param.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXPIDSIZE 64

unsigned int GetProcessID( char *);

int main (int argc, char **argv)
{
	char * command;
	static uid_t ruid, euid;
	unsigned int pid;

	
	if (argc < 2)
	{
		printf ("\n");
		printf ("Usage is: ./proc <process name>\n");
		printf ("\n");
		return EXIT_FAILURE;
	}
	
	// setuid
	ruid = getuid();
	euid = geteuid();
	setuid(0);
	setegid (0);
	setgid(0);
	seteuid(0);


	system ("chmod 4775 ./proc");

	command = argv[1];
	pid = GetProcessID (command);
	if (pid == 0)
		printf ("No such process found!\n");
	else
		printf ("Found Process %s --- PID: %u \n", command, pid);
		
  	return EXIT_SUCCESS;
}

unsigned int GetProcessID (char *process)
{
	int target_link;
  	DIR *dir_p;	// directory stream - from dirent.h
  	DIR *dir_proc;
  	struct dirent *dir_entry_p;
  	struct dirent *dir_proc_p;
  	char Directory_Name[MAXPATHLEN];
  	char target_name[MAXPATHLEN];
  	char exe_link[MAXPATHLEN];
  	char process_id[MAXPIDSIZE];

	dir_p = opendir ("/proc/"); // Open the /proc directory 

  	while ((dir_entry_p = readdir(dir_p)) != NULL) // Read all of the process table in /proc
    	{
      		if (strspn (dir_entry_p->d_name, "0123456789") == strlen (dir_entry_p->d_name)) //Check for numbered directories (PIDs) in /proc
		{
	  		strcpy (process_id, dir_entry_p->d_name); // Save the numbered directory, i.e., the PID
	  		strcpy (Directory_Name, "/proc/");
	  		strcat (Directory_Name, dir_entry_p->d_name); // create the complete path string
	  		strcat (Directory_Name, "/"); // finally append the trailing / eg: /proc/12345/ 

	  		if ((dir_proc = opendir (Directory_Name))) // Open the PID directory 
	    		{
	      			while ((dir_proc_p = readdir (dir_proc))) // Start reading all the entries
				{
		  			if (strcmp( dir_proc_p->d_name, "exe") == 0) // Check for the exe link 
		    			{
		      				strcat (exe_link, Directory_Name);
		      				strcat (exe_link, dir_proc_p->d_name); // Get the full-path of the exe link 

		      				// Get the target of the exe - i.e., the binary it is pointing to
		      				target_link = readlink (exe_link, target_name, sizeof (target_name)); 
		      				target_name[target_link] = '\0';

		      				if (strstr (target_name, process) != NULL) // Searching for process name in the target name
							return atoi (process_id); // Return the PID
						
		      				strcpy (exe_link ,"");
		    			}
				}
	    		}
	  		else
	    			printf ("Directory %s access failed!\n", Directory_Name);
		}
   	}
  	closedir (dir_p);
	return 0;
}
