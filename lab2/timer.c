#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "timer.h"

unsigned long counter = 0;
unsigned int hookid;

int timer_set_square(unsigned long timer, unsigned long freq) {

	if (timer < 0 || timer > 2 || freq <= 0)	/*check if timer is 0, 1, or 2*/
		return 1;							/*and if frequency is bigger than 0*/

	char c;

	timer_get_conf(timer, &c);

	unsigned short div = TIMER_FREQ/freq;	/*calculate value to output to counter*/

	char msb = div >> 8;					/*split the 2-byte short into two 1-byte chars*/
	char lsb = div;							/*msb = most significant part, lsb = least significant part*/

	c = c | SQUAREWAVE_CONFIG;				/*adapt the timer config in order to prepare it to change frequency*/

	port_t port;

	switch(timer)
	{
	case 0: port = TIMER_0; break;
	case 1: port = TIMER_1; break;
	case 2: port = TIMER_2; break;
	}

	if(sys_outb(port, lsb) != OK)
	{
		printf("Error in sys_outb\n");
		return 1;
	}
	if(sys_outb(port, msb) != OK)
	{
		printf("Error in sys_outb\n");
		return 1;
	}

	return 0;
}

int timer_subscribe_int(void ) {
	hookid = HOOK_ID_1;
	int notification;

	notification = sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqsetpolicy with error code %d\n", notification);
	}

	notification = sys_irqenable(&hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqenable with error code %d\n", notification);
	}

	return BIT(HOOK_ID_1);
}

int timer_unsubscribe_int() {
	int notification;

	notification = sys_irqdisable(&hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqdisable with error code %d\n", notification);
		return 1;
	}

	notification = sys_irqrmpolicy(&hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqdisable with error code %d\n", notification);
		return 1;
	}

	return 0;
}

void timer_int_handler() {
	counter++;
}

int timer_get_conf(unsigned long timer, unsigned char *st) {

	if (timer < 0 || timer > 2)		/*check if timer is 0, 1 or 2*/
		return 1;

	port_t port;
	unsigned char rb;

	switch(timer)
	{
	case 0: port = TIMER_0; rb = SELECT_TIMER0; break;
	case 1: port = TIMER_1; rb = SELECT_TIMER1; break;
	case 2: port = TIMER_2; rb = SELECT_TIMER2; break;
	}

	if(sys_outb(TIMER_CTRL, rb) != OK)
	{
		printf("Error in sys_outb\n");
		return 1;
	}

	if(sys_inb(port, (long unsigned int*) st) != OK)
	{
		printf("Error in sys_inb\n");
		return 1;
	}

	return 0;
}

int timer_display_conf(unsigned char conf) {
	
	printf("Timer Status byte: 0x%x\n", conf);

	unsigned char c = (conf & BIT(7)) >> 7;
	printf("Output value: %d\n", c);

	c = (conf & BIT(6)) >> 6;
	printf("Null count: %d\n", c);

	printf("Access Type: ");

	if(conf & BIT(4))
	{
		printf("LSB");

		if(conf & BIT(5))
		{
			printf(" + MSB");
		}
	}
	else if(conf & BIT(5))
	{
		printf("MSB");
	}

	printf("\n");

	c = conf << 4;
	c = c >> 5;

	printf("Programmed mode: ");
	switch(c)
	{
	case MODE_0: printf(MODE0); break;
	case MODE_1: printf(MODE1); break;
	case MODE_2a: printf(MODE2); break;
	case MODE_2b: printf(MODE2); break;
	case MODE_3a: printf(MODE3); break;
	case MODE_3b: printf(MODE3); break;
	case MODE_4: printf(MODE4); break;
	case MODE_5: printf(MODE5); break;
	}
	printf("\n");

	c = conf & BIT(0);
	printf("BCD: %d\n", c);

	return 0;
}

int timer_test_square(unsigned long freq) {
	
	timer_set_square(COUNTER_0, freq);

	return 0;
}

int timer_test_int(unsigned long time) {
	if (time == 0)
	{
		printf("Error: time must be bigger than 0\n");
		return 1;
	}


	unsigned int second = 1;
	int irq_subscription = timer_subscribe_int();
	int r;
	int ipc_status;
	message msg;

	while (counter <= time*60)
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
				if (msg.NOTIFY_ARG & irq_subscription)
				{
					timer_int_handler();
					if (counter % 60 == 0)
					{
						printf("Second %d\n", second);
						second++;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	if (timer_unsubscribe_int() != 0)
	{
		printf("Error: failed to unsubscribe\n");
		return 1;
	}

	return 0;
}

int timer_test_config(unsigned long timer) {
	char c;

	if(timer_get_conf(timer, &c) != 0)
	{
		printf("Error: invalid timer value\n");
		return 1;
	}

	timer_display_conf(c);

	return 0;
}
