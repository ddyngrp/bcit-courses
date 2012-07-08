# Change the default compiler to clang
CC		= clang

# Modify the system default CFLAGS
CFLAGS	+= -Wall -DDEBUG

# Declare name of the kernel module
KMOD	= control_module

# Enumerate source files for kernel module
SRCS	= control_module.c

clean	:
	rm -f \@ machine x86 *.o *.ko export_syms

# Include kernel module Makefile
.include <bsd.kmod.mk>
