# Change the default compiler to clang
CC		= clang

# Modify the system default CFLAGS
CFLAGS	+= -Wall -DDEBUG

# Declare name of the kernel module
KMOD	= control_module

# Enumerate source files for kernel module
SRCS	= control_module.c

distclean	:
	rm \@ machine x86

# Include kernel module Makefile
.include <bsd.kmod.mk>
