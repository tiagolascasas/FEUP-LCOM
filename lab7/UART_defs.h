#ifndef __UARTDEFS_H
#define __UARTDEFS_H

/*UART ports*/

#define COM1 0x3F8
#define COM2 0x2F8

/*UART registers*/

#define RBR 0
#define THR 0
#define LSR 5
#define LCR 3
#define DDL 0
#define DLM 1
#define IER 1
#define IIR 2
#define FCR 2

/*hook id and IRQ*/

#define HOOK_ID_4 4
#define HOOK_ID_5 5
#define COM1_IRQ 3
#define COM2_IRQ 4

/*IER configuration*/

#define ENABLE_INT 0b00000011

/*bit manipulation*/

#define BIT(n) (0x01<<(n))

#endif /*__UARTDEFS_H*/
