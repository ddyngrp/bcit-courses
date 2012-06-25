# Change the default compiler to clang
CC		= clang

# Modify the system default CFLAGS
CFLAGS	+= -Wall -pedantic -DDEBUG

OBJS	= control_userland.o

c_ul	: ${OBJS}
	${CC} ${CFLAGS} -o ${.TARGET} ${.ALLSRC}

${OBJS}	: ${.PREFIX}.c
	${CC} ${CFLAGS} -c ${.PREFIX}.c

clean	:
	rm ${OBJS} c_ul
