# Makefile for lab2

COMPILER_TYPE= gnu

CC= gcc

PROG= lab3
SRCS= lab3.c test3.c Keyboard.c timer.c kbd_read_asm.S

CCFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
