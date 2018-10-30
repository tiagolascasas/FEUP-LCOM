#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "test3.h"
#include "timer.h"
#include "i8254.h"

int kbd_test_scan(unsigned short ass) {
	unsigned int irq_set_kbc = kbd_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned char read;
	char flag = 0;
	char flag_esc = 0;
	unsigned char read2;

	if (ass)
		printf("Executing kbd_test_scan using Assembly\n");
	else
		printf("Executing kbd_test_scan using C\n");

	while (1) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_kbc) {
					if (ass) {
						read = kbd_read_asm();	/*read byte using Asm handler*/
					} else
						read = kbd_read_c(); /*read byte using C handler*/

					if (read == 0)//0 is the error code of both kbd_read_c and kbd_read_asm
							{
						printf(
								"Error: it wasn't possible to read from keyboard\n");
						return 1;
					}

					if (flag == 0) {
						if (read == TWO_BYTE_SCAN_CODE) {
							flag = 1;
							read2 = read;
						} else {
							printScanCode(read);
						}
					} else {
						flag = 0;
						printLongScanCode(read, read2);
					}

					if (read == ESC_BREAK_CODE) {
						flag_esc = 1;
						break;
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

	return 0;
}

int kbd_test_leds(unsigned short n, unsigned short *leds) {
	unsigned int irq_set_timer = timer_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned char read;
	char flag = 0;
	char flag_esc = 0;
	unsigned char read2;
	char flag_leds = 0;
	unsigned char ledCodes = 0;

	unsigned int counter = 0;

	unsigned int numberOfInterrupts = n * STANDARD_FREQ;
	unsigned int vectorIndex = 0;

	while (counter <= numberOfInterrupts) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_timer) {
					counter++;
					if (counter % 60 == 0) {
						unsigned char command = SET_LEDS;
						//kbd_writeCMD(command);

						printf("led %d\n", leds[vectorIndex]);
						setLeds(&ledCodes, leds[vectorIndex]);
						kbd_write(command, ledCodes);

						vectorIndex++;
						flag_leds = 0;
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

	if (timer_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	return 0;
}

int kbd_test_timed_scan(unsigned short n) {
	unsigned int irq_set_kbc = kbd_subscribe_int();
	unsigned int irq_set_timer = timer_subscribe_int();
	int r;
	int ipc_status;
	message msg;
	unsigned char read;
	char flag = 0;
	char flag_esc = 0;
	unsigned char read2;
	unsigned int time_limit = STANDARD_FREQ * n;
	unsigned int counter = 0;

	if (n <= 0) {
		printf("Error: invalid input\n");
		return 1;
	}

	while (counter <= time_limit) {
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("Error: driver_receive failed with error code %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_kbc) {
					read = kbd_read_c();
					counter = 0;

					if (read == 0) {
						printf(
								"Error: it wasn't possible to read from keyboard\n");
						return 1;
					}

					if (flag == 0) {
						if (read == TWO_BYTE_SCAN_CODE) {
							flag = 1;
							read2 = read;
						} else {
							printScanCode(read);
						}
					} else {
						flag = 0;
						printLongScanCode(read, read2);
					}

					if (read == ESC_BREAK_CODE) {
						flag_esc = 1;
						break;
					}
				}

				if (msg.NOTIFY_ARG & irq_set_timer) {
					counter++;
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

	if (timer_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	if (kbd_unsubscribe_int() != 0) {
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	return 0;
}
