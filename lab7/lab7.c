#include <string.h>
#include <errno.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "UART_defs.h"

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	sef_startup();
	printf("lab7 starting\n");

	proc_args(argc, argv);
	return 0;
}

static void print_usage(char **argv)
{
	printf("%s usage:\n", argv[0]);
	printf("service run %s -args \"conf 1|2\"\n", argv[0]);
	printf("service run %s -args \"poll ...\"\n", argv[0]);
	printf("service run %s -args \"int 1|2 0(tx)|1(rx) <bits> <stop> <parity> <rate> <string>\"\n", argv[0]);
	printf("service run %s -args \"fifo ...\"\n", argv[0]);
}

static int proc_args(int argc, char **argv)
{
	if (strncmp(argv[1], "conf", strlen("conf")) == 0) {
		char com = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (com== ULONG_MAX)
			return 1;
		if (com == 1)
		{
			printf("test7::ser_test_conf(0x%x)\n", COM1);
			return ser_test_conf(COM1);
		}
		else if (com == 2)
		{
			printf("test7::ser_test_conf(0x%x)\n", COM2);
			return ser_test_conf(COM2);
		}
		else return 1;
	}
	else if (strncmp(argv[1], "send", strlen("send")) == 0)
	{
		printf("test7::send_byte\n");
		return send_byte();
	}
	else if (strncmp(argv[1], "rec-int", strlen("rec-int")) == 0)
	{
		printf("test7::receive_byte_int\n");
		return receive_byte_int();
	}
	else if (strncmp(argv[1], "rec-poll", strlen("rec-poll")) == 0)
	{
		printf("test7::receive_byte_poll\n");
		return receive_byte_poll();
	}
	else
	{
		printf("test7: %s - no valid function!\n", argv[1]);
		return 1;
	}
}

static unsigned long parse_ulong(char *str, int base)
{
	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("test7: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
