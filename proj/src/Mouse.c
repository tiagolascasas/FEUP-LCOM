#include "Mouse.h"

unsigned int mouse_hookid;

int mouse_subscribe_int(void)
{
	mouse_hookid = HOOK_ID_3;

	int notification;

	notification = sys_irqsetpolicy(MOUSE_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &mouse_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqsetpolicy (mouse) with error code %d\n", notification);
	}

	notification = sys_irqenable(&mouse_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqenable (mouse) with error code %d\n", notification);
	}
	return BIT(HOOK_ID_3);
}

int mouse_unsubscribe_int(void)
{
	int notification;

	notification = sys_irqdisable(&mouse_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqdisable (mouse) with error code %d\n", notification);
		return 1;
	}

	notification = sys_irqrmpolicy(&mouse_hookid);

	if (notification != OK)
	{
		printf("Error in sys_irqdisable (mouse) with error code %d\n", notification);
		return 1;
	}
	return 0;
}

int mouse_writeCMD(unsigned char command, unsigned short port)
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
			sys_outb(port, command);
			return 0;
		}
	}
	return -1;
}

int mouse_write(unsigned char kbc_command, unsigned char ps2_command, char hasArgs, unsigned char argument)
{
	int counter;
	unsigned long status;
	unsigned long response;

	if (mouse_writeCMD(kbc_command, CTRL_REG))	/*write kbc command to port 0x64*/
	{
		printf("Error issuing kbc command\n");
		return -1;
	}

	do
	{
		if (mouse_writeCMD(ps2_command, IN_BUF_MOUSE))		/*write ps2 command to port 0x60*/
		{
			printf("Error issuing ps2 command\n");
			return -1;
		}

		if(sys_inb(OUT_BUF_MOUSE, &response) != OK)		/*get response*/
		{
			printf("Error reading response\n");
			return -1;
		}
	} while (response != ACK);				/*if response is not ACK, retry command*/

	if (!hasArgs)			/*check if the ps2 command has args*/
		return 0;
	do
	{
		if (mouse_writeCMD(kbc_command, CTRL_REG))	/*write kbc command to port 0x64*/
		{
			printf("Error issuing kbc command\n");
			return -1;
		}

		if (mouse_writeCMD(argument, IN_BUF_MOUSE))		/*write argument of ps2 command to port 0x60*/
		{
			printf("Error issuing argument of ps2 command\n");
			return -1;
		}

		if(sys_inb(OUT_BUF_MOUSE, &response) != OK)		/*get response*/
		{
			printf("Error reading response\n");
			return -1;
		}
	} while (response != ACK);				/*if response is not ACK, retry 0xD4 and command*/

	return 0;
}

unsigned char mouse_read()
{
	unsigned char input;
	unsigned long status;

	int counter;

	for(counter = 0; counter < RETRIES; counter++)
	{
		if (sys_inb(STAT_REG, &status) != OK)
		{
			printf("Error in sys_inb\n");
			return -1;
		}

		if(status & OBF)
		{
			if (sys_inb(OUT_BUF, (long unsigned int*)&input) != OK)
			{
				printf("Error in sys_inb\n");
				return -1;
			}

			if ((status & (PAR | TIMEOUT)) == 0)
				return input;
			else return -1;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
	return -1;
}

signed short mouse_join_sig_and_number(char sign, unsigned char number)
{
	signed short result;
	if (sign)
		return result = SIGN_1 | number;
	else return result = SIGN_0 | number;
}

Mouse* createMouse(Bitmap* pointer)
{
	Mouse* mouse = (Mouse*) malloc(sizeof(Mouse));

	mouse->pointer = pointer;
	mouse->leftPressed = 0;
	mouse->rightPressed = 0;
	mouse->middlePressed = 0;
	mouse->x = MOUSE_START_X;
	mouse->y = MOUSE_START_Y;
	mouse->packet[0] = 0;
	mouse->packet[1] = 0;
	mouse->packet[2] = 0;
	mouse->nextPacket = 0;
}

void updateMouse(Mouse* mouse, unsigned char packet)
{
	if ((packet & BIT(3)) && (mouse->nextPacket == 0))
	{
		mouse->packet[0] = packet;
		mouse->nextPacket = 1;
	}
	else if (mouse->nextPacket == 1)
	{
		mouse->packet[1] = packet;
		mouse->nextPacket = 2;
	}
	else if (mouse->nextPacket == 2)
	{
		mouse->packet[2] = packet;
		mouse->nextPacket = 0;
		updateMouseMoves(mouse);
		updateMouseButtons(mouse);
	}
}

void drawMouse(Mouse* mouse, char transparency, short trColor)
{
	drawBitmap(mouse->pointer, mouse->x, mouse->y, ALIGN_LEFT, transparency, trColor);
}

void updateMouseMoves(Mouse* mouse)
{
	short x = mouse_join_sig_and_number(mouse->packet[0] & BIT(4), mouse->packet[1]);
	short y = mouse_join_sig_and_number(mouse->packet[0] & BIT(5), mouse->packet[2]);

	mouse->x += x;
	mouse->y -= y;

	if (mouse->x + mouse->pointer->bitmapInfoHeader.width >= getHorResolution())
		mouse->x = getHorResolution() - mouse->pointer->bitmapInfoHeader.width;

	if (mouse->y + mouse->pointer->bitmapInfoHeader.height >= getVerResolution())
		mouse->y = getVerResolution() - mouse->pointer->bitmapInfoHeader.height;

	if (mouse->x <= 0)
		mouse->x = 0;

	if (mouse->y <= 0)
		mouse->y = 0;
}

void updateMouseButtons(Mouse* mouse)
{
	mouse->leftPressed = mouse->packet[0] & BIT(0);
	mouse->middlePressed = mouse->packet[0] & BIT(2);
	mouse->rightPressed = mouse->packet[0] & BIT(1);
}
