#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "Timer.h"

unsigned int timer_hookid;

int timer_subscribe_int(void ) {
	timer_hookid = HOOK_ID_1;
	int notification;

	notification = sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqsetpolicy with error code %d\n", notification);
	}

	notification = sys_irqenable(&timer_hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqenable with error code %d\n", notification);
	}

	return BIT(HOOK_ID_1);
}

int timer_unsubscribe_int() {
	int notification;

	notification = sys_irqdisable(&timer_hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqdisable with error code %d\n", notification);
		return 1;
	}

	notification = sys_irqrmpolicy(&timer_hookid);
	if (notification != OK)
	{
		printf("Error in sys_irqdisable with error code %d\n", notification);
		return 1;
	}

	return 0;
}
