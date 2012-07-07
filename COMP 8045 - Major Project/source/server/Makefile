# Change the default compiler to clang
CC		= clang

# Modify the system default CFLAGS
CFLAGS	+= -Wall -pedantic -DDEBUG

OBJS	= server_control.o
PROG	= server_control

${PROG}	: ${OBJS}
	${CC} ${CFLAGS} -o ${.TARGET} ${.ALLSRC}

${OBJS}	: ${.PREFIX}.c
	${CC} ${CFLAGS} -c ${.PREFIX}.c

clean	:
	rm ${OBJS} ${PROG}
