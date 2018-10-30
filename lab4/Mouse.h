#ifndef __MOUSE_H
#define __MOUSE_H
#include "mouse_defs.h"
#include "i8042.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>

int mouse_subscribe_int(void);

int mouse_unsubscribe_int(void);

int mouse_writeCMD(unsigned char command, unsigned short port);

int mouse_write(unsigned char kbc_command, unsigned char ps2_command, char hasArgs, unsigned char argument);

unsigned char mouse_read();

void mouse_print_packet(unsigned char *packet);

signed short mouse_join_sig_and_number(char sign, unsigned char number);

void mouse_print_status(unsigned char *status);

unsigned char mouse_get_packet(unsigned char *packet, unsigned int irq_set_mouse);

#endif /* __MOUSE_H */
