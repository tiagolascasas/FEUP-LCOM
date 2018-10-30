#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "i8042.h"

int kbd_subscribe_int(void);

int kbd_unsubscribe_int(void);

//int kbd_read_asm(void);

char kbd_read_c(void);

int kbd_writeCMD(char command);

int kbd_write(char command, char argument);

void printScanCode(unsigned char read);

void printLongScanCode(unsigned char read, unsigned char read2);

void setLeds(unsigned char * ledCodes, unsigned short led);

#endif /* __KEYBOARD_H */
