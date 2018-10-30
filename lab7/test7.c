#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "UART.h"
#include "UART_defs.h"

int ser_test_conf(unsigned short base_addr)
{
	char byte;

    if (base_addr == COM1)
    {
    	printf("COM1 configuration:");
    	printf("LCR = 0x%x\n", uart_read(base_addr, LCR));
    	printf("DLM = 0x%x DLL = 0x%x\n", uart_read(base_addr, DLM), uart_read(base_addr, DDL));
    	printf("IER = 0x%x\n", uart_read(base_addr, IER));
    	return 0;
    }
    else if (base_addr == COM2)
    {
    	printf("COM2 configuration:");
    	printf("LCR = 0x%x\n", uart_read(base_addr, LCR));
    	printf("DLM = 0x%x DLL = 0x%x\n", uart_read(base_addr, DLM), uart_read(base_addr, DDL));
    	printf("IER = 0x%x\n", uart_read(base_addr, IER));
    	return 0;
    }
    else
    	printf("Invalid port\n");
    return 1;
}

int send_byte()
{
	uart_send_byte(COM1, 't');
}

int receive_byte_int()
{
    int com1_irq = uart_subscribe_int(COM1);
	int r;
	int ipc_status;
	message msg;

	uart_enable_int();
	printf("IER status 0x%x\n", uart_read(COM1, IER));

	while (1)
	{
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0)
		{
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status))
		{
			switch (_ENDPOINT_P(msg.m_source))
			{
			case HARDWARE:
				if (msg.NOTIFY_ARG & com1_irq)
				{
					printf("int\n");
				}
				break;
			default:
				break;
			}
		}
	}

    uart_unsubscribe_int(COM1);
    return 0;
}

int receive_byte_poll()
{
	while (1)
	{
		char reg = uart_read(COM1, LSR);
		if (reg & BIT(0))
		{
			char byte;
			sys_inb(COM1, &byte);
			printf("byte %c\n", byte);
			break;
		}
	}
	return 0;
}
