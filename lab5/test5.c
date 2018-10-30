#include "test5.h"
#include "vbe.h"
#include "video_defs.h"
#include <machine/int86.h>

void *test_init(unsigned short mode, unsigned short delay){

	lm_init();
	vg_init(mode);

	if (timer_test_int((unsigned long) delay) != 0)
		printf("timer_test_int() didn't exit successfully");

	if (vg_exit() != 0)
		printf("vg_exit() didn't exit successfully\n");
	else
		printf("vg_exit() exited successfully\n");
}

int test_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color)
{
	lm_init();
	vg_init(MODE_1024X768);

	unsigned int irq_set_kbc = kbd_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned char read;
	char flag_esc = 0;

	if (vg_draw_square(x, y, size, color) != 0)
	{
		printf("Invalid parameters\n");
	}

	while (1) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source))
			{
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_kbc) {
					read = kbd_read_c(); /*read byte using C handler*/
					if (read == 0)
					{
						printf("Error: it wasn't possible to read from keyboard\n");
						return 1;
					}
					if (read == ESC_BREAK_CODE)
						flag_esc = 1;
				}
				break;

			default:
				break;
			}

			if (flag_esc) {
				break;
			}
		}
	}

	if (kbd_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}
	if (vg_exit() != 0)
		printf("vg_exit() didn't exit successfully\n");
	else
		printf("vg_exit() exited successfully\n");
	printf("test_square() ended\n");

	return 0;
}

int test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color)
{
	lm_init();
	vg_init(MODE_1024X768);

	unsigned int irq_set_kbc = kbd_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned char read;
	char flag_esc = 0;

	if (vg_draw_line(xi, yi, xf, yf, color) != 0)
	{
		printf("Invalid parameters\n");
	}

	while (1) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source))
			{
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_kbc) {
					read = kbd_read_c(); /*read byte using C handler*/
					if (read == 0)
					{
						printf("Error: it wasn't possible to read from keyboard\n");
						return 1;
					}
					if (read == ESC_BREAK_CODE)
						flag_esc = 1;
				}
				break;

			default:
				break;
			}

			if (flag_esc) {
				break;
			}
		}
	}

	if (kbd_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}
	if (vg_exit() != 0)
		printf("vg_exit() didn't exit successfully\n");
	else
		printf("vg_exit() exited successfully\n");
	printf("test_line() ended\n");
	return 0;

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {
	lm_init();
	vg_init(MODE_1024X768);

	unsigned int irq_set_kbc = kbd_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned char read;
	char flag_esc = 0;

	if (vg_draw_xpm(xi, yi, xpm) != 0)
	{
		printf("Invalid parameters\n");
	}

	while (1) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source))
			{
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_kbc) {
					read = kbd_read_c(); /*read byte using C handler*/
					if (read == 0)
					{
						printf("Error: it wasn't possible to read from keyboard\n");
						return 1;
					}
					if (read == ESC_BREAK_CODE)
						flag_esc = 1;
				}
				break;

			default:
				break;
			}

			if (flag_esc) {
				break;
			}
		}
	}

	if (kbd_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}
	if (vg_exit() != 0)
		printf("vg_exit() didn't exit successfully\n");
	else
		printf("vg_exit() exited successfully\n");
	printf("test_xpm() ended\n");
	return 0;
}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time)
{
	lm_init();
	vg_init(MODE_1024X768);

	unsigned int irq_set_kbc = kbd_subscribe_int();
	unsigned int irq_set_timer = timer_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned char read;
	char flag_esc = 0;

	Sprite* sprite = (Sprite*) create_move(xpm, xi, yi, time, hor, delta);
	if (sprite == NULL)
	{
		printf("Error: it is not possible to move the specified length starting from the specified position\n");

		if (kbd_unsubscribe_int() != 0) {
			printf("Error: failed to unsubscribe\n");
			return 1;
		}
		if (timer_unsubscribe_int() != 0) {
			printf("Error: failed to unsubscribe\n");
			return 1;
		}

		if (vg_exit() != 0)
			printf("vg_exit() didn't exit successfully\n");
		else
			printf("vg_exit() exited successfully\n");
		printf("test_move() ended\n");
		return 1;
	}

	while (1) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source))
			{
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_kbc) {
					read = kbd_read_c();
					if (read == 0)
					{
						printf("Error: it wasn't possible to read from keyboard\n");
						return 1;
					}
					if (read == ESC_BREAK_CODE)
						flag_esc = 1;
				}
				if (msg.NOTIFY_ARG & irq_set_timer)
				{
					if (move_sprite(sprite, DT, xi, yi, delta) != 0)
					{
						printf("Error moving sprite\n");
					}
				}
				break;

			default:
				break;
			}

			if (flag_esc) {
				break;
			}
		}
	}

	if (kbd_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}
	if (timer_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	vg_exit();
	printf("test_move() ended\n");
	return 0;
}

int test_controller()
{
	lm_init();

	vbe_info_t info;	//defined in vbe.h

	vbe_get_info(&info);

	printf("\nCapabilities:\n");
	if (info.Capabilities && BIT(0))
		printf("DAC width is switchable to 8 bits per primary color\n");
	else printf("DAC is fixed width, with 6 bits per primary color\n");
	if (info.Capabilities && BIT(1))
		printf("Controller is not VGA compatible\n");
	else printf("Controller is VGA compatible\n");
	if (info.Capabilities && BIT(2))
		printf("When programming large blocks of information to the RAMDAC, use the blank bit in Function 09h\n");
	else printf("Normal RAMDAC operation\n");

	printf("Total VRAM memory: %d 64KB units\n", info.TotalMemory);

}

