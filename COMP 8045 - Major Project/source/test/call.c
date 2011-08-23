#include <sys/types.h>
#include <sys/module.h>
#include <sys/syscall.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc __unused, char **argv __unused)
{
    int syscall_num;
    struct module_stat stat;

    stat.version = sizeof(stat);
    modstat(modfind("sys/net_hiding"), &stat);
    syscall_num = stat.data.intval;
    return syscall (syscall_num);
}
