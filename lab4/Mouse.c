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
			return 0;
		}

		if(status & OBF)
		{
			if (sys_inb(OUT_BUF, (long unsigned int*)&input) != OK)
			{
				printf("Error in sys_inb\n");
				return 0;
			}

			if ((status & (PAR | TIMEOUT)) == 0)
				return input;
			else return 0;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}
	return -1;
}

void mouse_print_packet(unsigned char *packet)
{
	signed short x, y;

	x = mouse_join_sig_and_number(packet[0] & BIT(4), packet[1]);
	y = mouse_join_sig_and_number(packet[0] & BIT(5), packet[2]);
	printf("B1=0x%x B2=0x%x B3=0x%x ", packet[0], packet[1], packet[2]);
	printf("LB=0x%x MB=0x%x RB=0x%x ", packet[0] & BIT(0), (packet[0] & BIT(2)) >> 2,(packet[0] & BIT(1)) >> 1);
	printf("XOV=0x%x YOV=0x%x ", packet[0] & BIT(6) >> 6, packet[0] & BIT(7) >> 7);
	printf("X=%d Y=%d\n", x, y);
}

signed short mouse_join_sig_and_number(char sign, unsigned char number)
{
	signed short result;
	if (sign)
		return result = SIGN_1 | number;
	else return result = SIGN_0 | number;
}

void mouse_print_status(unsigned char *status)
{
	if (status[0] & BIT(6))
		printf("Remote (polled) mode enabled\n");
	else printf ("Stream mode enabled\n");
	if (status[0] & BIT(5))
		printf("Data reporting enabled\n");
	else printf("Data reporting disabled\n");
	if (status[0] & BIT(4))
		printf("Scaling is set to 2:1\n");
	else printf("Scaling is set to 1:1\n");
	if (status[0] & BIT(0))
		printf("Left button is currently pressed\n");
	else printf("Left button is currently not pressed\n");
	if (status[0] & BIT(2))
		printf("Middle button is currently pressed\n");
	else printf("Middle button is currently not pressed\n");
	if (status[0] & BIT(1))
		printf("Right button is currently pressed\n");
	else printf("Right button is currently not pressed\n");
	printf("The current resolution is %d\n", status[1]);
	printf("The current sample rate is %d\n", status[2]);
}

unsigned char mouse_get_packet(unsigned char *packet, unsigned int irq_set_mouse){
	int r;
	int ipc_status;
	message msg;
	unsigned char read_packet;
	unsigned short loop_counter = 0;
	unsigned char packet_byte_counter = 0;

	while (packet_byte_counter < 3) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
		{
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_mouse)
				{
					read_packet = mouse_read();
					if (read_packet & BIT(3))
					{
						packet[0] = read_packet;
						packet_byte_counter = 1;
					}
					else if (packet_byte_counter == 1)
					{
						packet[1] = read_packet;
						packet_byte_counter++;
					}
					else if (packet_byte_counter == 2)
					{
						packet[2] = read_packet;
						packet_byte_counter++;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	return 0;
}
