# Change the default compiler to clang
CC		= clang

# Modify the system default CFLAGS
CFLAGS	+= -Wall -pedantic -DDEBUG

OBJS	= client_control.o

client_control	: ${OBJS}
	${CC} ${CFLAGS} -o ${.TARGET} ${.ALLSRC}

${OBJS}	: ${.PREFIX}.c
	${CC} ${CFLAGS} -c ${.PREFIX}.c

clean	:
	rm ${OBJS} client_control
