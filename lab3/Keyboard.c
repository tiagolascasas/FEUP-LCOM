#include "Keyboard.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>

unsigned int kbd_hookid;
unsigned int timer_hookid;

int kbd_subscribe_int(void)
{
	kbd_hookid = HOOK_ID_2;

	int notification;

	notification = sys_irqsetpolicy(KBD_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &kbd_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqsetpolicy (keyboard) with error code %d\n", notification);
	}

	notification = sys_irqenable(&kbd_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqenable (keyboard) with error code %d\n", notification);
	}
	return BIT(HOOK_ID_2);
}

int kbd_unsubscribe_int(void)
{
	int notification;

	notification = sys_irqdisable(&kbd_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqdisable (keyboard) with error code %d\n", notification);
		return 1;
	}

	notification = sys_irqrmpolicy(&kbd_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqdisable (keyboard) with error code %d\n", notification);
		return 1;
	}
	return 0;
}

char kbd_read_c(void)
{
	unsigned char code;
	unsigned long status;

	int counter;

	for(counter = 0; counter < RETRIES; counter++)
	{
		if (sys_inb(STAT_REG, &status) != OK)
		{
			printf("Error in sys_inb\n");
			return 0;
		}

		if(status & OBF)
		{
			if (sys_inb(OUT_BUF, (long unsigned int*)&code) != OK)
			{
				printf("Error in sys_inb\n");
				return 0;
			}

			if ((status & (PAR | TIMEOUT)) == 0)
				return code;
			else return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}

	return -1;
}

int kbd_writeCMD(char command)
{
	int counter;
	unsigned long status;

	for(counter = 0; counter < RETRIES; counter++)
	{
		if (sys_inb(STAT_REG, &status) != OK)
		{
			printf("Error in sys_inb\n");
			return -1;
		}

		if((status & IBF) == 0)
		{
			sys_outb(OUT_BUF, command);
			return 0;
		}
	}
	return -1;
}

int kbd_write(char command, char argument)
{
	int counter;
	unsigned long status;

	for(counter = 0; counter < RETRIES; counter++)
	{
		if (kbd_writeCMD(command))
		{
			printf("Error issuing command\n");
			return -1;
		}


		if(sys_outb(OUT_BUF, argument) != OK)
		{
			printf("Error in sys_outb\n");
			return -1;
		}
		return 0;

	}
	return -1;
}

void printScanCode(unsigned char read)
{
	if (!(read & BIT(7))) {
		printf("Makecode: 0x%x\n", read);
	} else
		printf("Breakcode: 0x%x\n", read);
}

void printLongScanCode(unsigned char read, unsigned char read2)
{
	if (!(read & BIT(7))) {
		printf("Makecode: 0x%x%x\n", read2, read);
	} else
		printf("Breakcode: 0x%x%x\n", read2, read);
}

void setLeds(unsigned char * ledCodes, unsigned short led)
{
	if (led == 0) {
		if (*ledCodes & BIT(LED_0_NUM))
			*ledCodes = *ledCodes & ~BIT(LED_0_NUM);
		else
			*ledCodes = *ledCodes | BIT(LED_0_NUM);

	} else if (led == 1) {
		if (*ledCodes & BIT(LED_1_CAPS))
			*ledCodes = *ledCodes & ~BIT(LED_1_CAPS);
		else
			*ledCodes = *ledCodes | BIT(LED_1_CAPS);

	} else if (led == 2) {
		if (*ledCodes & BIT(LED_2_SCROLL))
			*ledCodes = *ledCodes & ~BIT(LED_2_SCROLL);
		else
			*ledCodes = *ledCodes | BIT(LED_2_SCROLL);

	} else
		printf("Error: %d is not a valid led\n",
				led);
}
