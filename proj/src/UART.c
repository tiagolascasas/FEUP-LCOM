#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "UART.h"
#include "UART_defs.h"

unsigned int com1_hookid;
unsigned int com2_hookid;

int uart_subscribe_int(unsigned short com)
{
	int notification;

	if (com == COM1)
	{
		notification = sys_irqsetpolicy(COM1_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &com1_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqsetpolicy (COM1) with error code %d\n", notification);
		}

		notification = sys_irqenable(&com1_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqenable (COM1) with error code %d\n", notification);
		}
		printf("Subscribed\n");
		return BIT(HOOK_ID_4);
	}
	else if (com == COM2)
	{
		notification = sys_irqsetpolicy(COM2_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &com2_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqsetpolicy (COM2) with error code %d\n", notification);
		}

		notification = sys_irqenable(&com2_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqenable (COM2) with error code %d\n", notification);
		}
		return BIT(HOOK_ID_5);
	}
	else return -1;
}

int uart_unsubscribe_int(unsigned short com)
{
	int notification;

	if (com == COM1)
	{
		notification = sys_irqdisable(&com1_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqdisable (COM1) with error code %d\n", notification);
			return 1;
		}

		notification = sys_irqrmpolicy(&com1_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqdisable (COM1) with error code %d\n", notification);
			return 1;
		}
		return 0;
	}
	else if (com == COM2)
	{
		notification = sys_irqdisable(&com2_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqdisable (COM2) with error code %d\n", notification);
			return 1;
		}

		notification = sys_irqrmpolicy(&com2_hookid);

		if (notification != OK)
		{
			printf("Error in sys_irqdisable (COM2) with error code %d\n", notification);
			return 1;
		}
		return 0;
	}
	else return 1;
}

int uart_write(short arg, unsigned short port, unsigned char addr)
{
	if (sys_outb(port + addr, arg) != OK)
		return 1;
	else return 0;
}

char uart_read(unsigned short port, unsigned char addr)
{
	unsigned long reading;
	if (sys_inb(port + addr, &reading) != OK)
		return 0;
	else return (char)reading;
}

int uart_send_byte(unsigned short port, char byte)
{
	if (sys_outb(port + THR, byte) != OK)
		return 1;
	else return 0;
}

int uart_enable_int()
{
	unsigned char ier_content = uart_read(COM1, IER);
	ier_content |= ENABLE_INT;
	return uart_write(ier_content, COM1, IER);
}

void uart_clean()
{
	char reg;
	do
	{
		reg = uart_read(COM1, LSR);
		char byte = 0;
		if (reg & BIT(0))
		{
			byte = uart_read(COM1, RBR);
			printf("Cleansed UART byte %c\n", byte);
		}
	} while (reg & BIT(0));
}
