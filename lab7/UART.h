#ifndef __UART_H
#define __UART_H

int uart_subscribe_int(unsigned short com);

int uart_unsubscribe_int(unsigned short com);

int uart_write(short arg, unsigned short port, unsigned char addr);

char uart_read(unsigned short port, unsigned char addr);

int uart_send_byte(unsigned short port, char byte);

int uart_enable_int();

#endif /*__UART_H*/
