# Makefile for asterinix

COMPILER_TYPE= gnu

CC= gcc

PROG= asterinix
SRCS= Asterinix.c Timer.c Keyboard.c Mouse.c Graphics.c main.c VBE.c Bitmap.c
SRCS+= Game.c Stage.c Player.c Asteroid.c Sprite.c kbd_read_asm.S Bullet.c
SRCS+= Score.c RTC.c Utilities.c Highscores.c Asm_utils.S rtc_read_asm.S
SRCS+= UART.c

CCFLAGS= -Wall

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
