#include "Mouse.h"
#include "i8254.h"
#include "mouse_defs.h"

int test_packet(unsigned short cnt){

	if (cnt <= 0) {
		printf("Error: invalid input\n");
		return 1;
	}

	if (mouse_writeCMD(ENABLE_MOUSE, CTRL_REG) != 0) return 1;		/*enable mouse*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, STREAM_MODE, NO_ARG, NO_ARG) != 0) return 1;		/*set mouse to stream mode*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, ENABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;	/*set mouse to receive data packets*/

	unsigned int irq_set_mouse = mouse_subscribe_int();
	unsigned int loop_counter = 1;

	while (loop_counter <= cnt) {
		unsigned char packet[3];
		mouse_get_packet(packet, irq_set_mouse);
		printf("Packet no. %d\n", loop_counter);
		mouse_print_packet(packet);
		loop_counter++;
	}

	if (mouse_unsubscribe_int() != 0)
	{
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	if (mouse_write(WRITE_BYTE_TO_MOUSE, DISABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;
	if (mouse_writeCMD(DISABLE_MOUSE, CTRL_REG) != 0) return 1;

	printf("test_packet exited successfully\n");
	return 0;
}	
	
int test_async(unsigned short idle_time) {

	if (idle_time <= 0) {
		printf("Error: invalid input\n");
		return 1;
	}

	if (mouse_writeCMD(ENABLE_MOUSE, CTRL_REG) != 0) return 1;		/*enable mouse*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, STREAM_MODE, NO_ARG, NO_ARG) != 0) return 1;		/*set mouse to stream mode*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, ENABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;	/*set mouse to receive data packets*/

	unsigned int irq_set_mouse = mouse_subscribe_int();
	unsigned int irq_set_timer = timer_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned short counter;
	unsigned short time_limit = STANDARD_FREQ * idle_time;
	unsigned char packet[3];
	unsigned char read_packet;
	unsigned char packet_byte_counter;

	while (counter <= time_limit) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_mouse) {
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
						mouse_print_packet(packet);
						counter = 0;
					}
				}
				if (msg.NOTIFY_ARG & irq_set_timer) {
					counter++;
				}
				break;
			default:
				break;
			}

		}
	}

	if (timer_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	if (mouse_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	if (mouse_write(WRITE_BYTE_TO_MOUSE, DISABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;
	if (mouse_writeCMD(DISABLE_MOUSE, CTRL_REG) != 0) return 1;

	printf("test_async exited successfully\n");
	return 0;
}
	
int test_config(void) {
	unsigned int irq_set_mouse = mouse_subscribe_int();
	unsigned char counter = 0;
	unsigned char status[3];

	if (mouse_writeCMD(ENABLE_MOUSE, CTRL_REG) != 0) return 1;
	if (mouse_write(WRITE_BYTE_TO_MOUSE, STREAM_MODE, NO_ARG, NO_ARG) != 0) return 1;		/*set mouse to stream mode*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, ENABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;	/*set mouse to enable data packets*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, STATUS_REQUEST, NO_ARG, NO_ARG) != 0) return 1;	/*request status information*/

	for (counter = 0; counter < 3; counter++)
	{
		unsigned char read_byte = mouse_read();
		if (read_byte == READ_ERROR)
			return -1;
		status[counter] = read_byte;
	}

	printf("\n");
	mouse_print_status(status);

	if (mouse_write(WRITE_BYTE_TO_MOUSE, DISABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;	/*disable data reporting*/
	if (mouse_writeCMD(DISABLE_MOUSE, CTRL_REG) != 0) return 1;		/*disable mouse*/

	printf("\ntest_config exited successfully\n");
	return 0;
}
	
int test_gesture(short length) {

	if (mouse_writeCMD(ENABLE_MOUSE, CTRL_REG) != 0) return 1;		/*enable mouse*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, STREAM_MODE, NO_ARG, NO_ARG) != 0) return 1;		/*set mouse to stream mode*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, ENABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;	/*set mouse to receive data packets*/

	unsigned int irq_set_mouse = mouse_subscribe_int();
    int running = 1;
	int state = INIT;
	short x1, x2, y1, y2;
	short y0 = 0;

	while(running)
	{
		switch(state)
		{
		case INIT: ;
			unsigned char packet[3];
			if (mouse_get_packet(packet, irq_set_mouse) != 0)
				return -1;
			mouse_print_packet(packet);
			x2 = mouse_join_sig_and_number(packet[0] & BIT(4), packet[1]);
			y2 = mouse_join_sig_and_number(packet[0] & BIT(5), packet[2]);

			if(length > 0)
			{
				if(y2 > 0 && x2 > 0 && (packet[0] & BIT(1)))
				{
					y1 += y2;
					x1 += x2;

					if(y1 > length)
					{
						running = 0;
					}
				}
				else
				{
					y0 = 0;
					y1 = 0;
					x1 = 0;
				}
			}
			else
			{
				if(y2 < 0 && x2 < 0 && (packet[0] & BIT(1)))
				{
					y1 += y2;
					x1 += x2;

					if(y1 < length)
					{
						running = 0;
					}
				}
				else
				{
					y0 = 0;
					y1 = 0;
					x1 = 0;
				}
			}
			break;
		}
	}

	if (mouse_unsubscribe_int() != 0)
	{
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	if (mouse_write(WRITE_BYTE_TO_MOUSE, DISABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;
	if (mouse_writeCMD(DISABLE_MOUSE, CTRL_REG) != 0) return 1;

	printf("test_gesture exited successfully\n");
	return 0;
}
