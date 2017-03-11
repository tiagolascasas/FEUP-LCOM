#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>

#include "Keyboard.h"
#include "i8042.h"

unsigned int kbd_hookid;

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

unsigned short kbd_make_2byte_scancode(unsigned char scancode)
{
	unsigned short res = TWO_BYTE_GENERIC;
	res |= scancode;
	return res;
}

key_status_t* createKeyStatus()
{
	key_status_t* status = (key_status_t*) malloc(sizeof(key_status_t));

	status->key_w = RELEASED;
	status->key_a = RELEASED;
	status->key_s = RELEASED;
	status->key_d = RELEASED;
	status->key_arrow_up = RELEASED;
	status->key_arrow_down = RELEASED;
	status->key_arrow_left = RELEASED;
	status->key_arrow_right = RELEASED;
	status->key_esc = RELEASED;
	status->key_enter = RELEASED;
	status->two_byte = RELEASED;
}

void updateKeyStatus(key_status_t* key_status, scancode sc)
{
	if (sc != TWO_BYTE_INDICATOR)
	{
		if (!key_status->two_byte)
		{
			switch(sc)
			{
				case	MAKE_W:		key_status->key_w 	= PRESSED; break;
				case	BREAK_W: 	key_status->key_w 	= RELEASED; break;
				case	MAKE_A:		key_status->key_a 	= PRESSED; break;
				case	BREAK_A: 	key_status->key_a 	= RELEASED; break;
				case	MAKE_S:		key_status->key_s 	= PRESSED; break;
				case	BREAK_S: 	key_status->key_s 	= RELEASED; break;
				case	MAKE_D:		key_status->key_d 	= PRESSED; break;
				case	BREAK_D: 	key_status->key_d 	= RELEASED; break;

				case	MAKE_ESC: 	key_status->key_esc = PRESSED;	break;
				case	BREAK_ESC:	key_status->key_esc = RELEASED;	break;

				case	MAKE_ENTER: 	key_status->key_enter = PRESSED;	break;
				case	BREAK_ENTER:	key_status->key_enter = RELEASED;	break;

				default:	break;
			}
		}
		else
		{
			unsigned short two_byte_scancode = kbd_make_2byte_scancode(sc);

			switch(two_byte_scancode)
			{
				case	MAKE_ARROW_UP:		key_status->key_arrow_up = PRESSED; break;
				case	BREAK_ARROW_UP:		key_status->key_arrow_up = RELEASED; break;
				case	MAKE_ARROW_LEFT:	key_status->key_arrow_left = PRESSED; break;
				case	BREAK_ARROW_LEFT:	key_status->key_arrow_left = RELEASED; break;
				case	MAKE_ARROW_DOWN:	key_status->key_arrow_down = PRESSED; break;
				case	BREAK_ARROW_DOWN:	key_status->key_arrow_down = RELEASED; break;
				case	MAKE_ARROW_RIGHT:	key_status->key_arrow_right = PRESSED;break;
				case	BREAK_ARROW_RIGHT:	key_status->key_arrow_right = RELEASED;break;

				default: break;
			}
			key_status->two_byte = TWO_BYTE_NO;
		}
	}
	else
		key_status->two_byte = TWO_BYTE_YES;
}
