#include <minix/drivers.h>
#include "RTC.h"
#include "RTC_defs.h"

inline void rtc_disable_interrupts()
{
	asm("cli");
}

inline void rtc_enable_interrupts()
{
	asm("sti");
}

char rtc_read(int address)
{
	long reading;

	if (sys_outb(RTC_ADDR_REG, address) != OK) return -1;
	if (sys_inb(RTC_DATA_REG, &reading) != OK) return -1;
	return (char)reading;
}

int rtc_write(int address, char info)
{
	if (sys_outb(RTC_ADDR_REG, address) != OK) return -1;
	if (sys_outb(RTC_DATA_REG, info) != OK) return -1;
	return 0;
}

int rtc_get_date_and_time(char* date)
{
	rtc_disable_interrupts();

	char readA;
	do
	{
		readA = rtc_read_asm(REG_A);
	} while (readA & BIT(7));

	if (rtc_write(REG_B, CONF) != 0) return 1;

	date[5] = rtc_read_asm(SECONDS);
	date[4] = rtc_read_asm(MINUTES);
	date[3] = rtc_read_asm(HOURS);
	date[2] = rtc_read_asm(DAY);
	date[1] = rtc_read_asm(MONTH);
	date[0] = rtc_read_asm(YEAR);

	rtc_enable_interrupts();

	return 0;
}
