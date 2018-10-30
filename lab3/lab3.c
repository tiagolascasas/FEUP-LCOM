#include "timer.h"
#include "i8254.h"
#include "test3.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	sef_startup();
	sys_enable_iop(SELF);

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
}

static void print_usage(char **argv)
{
	printf("%s usage:\n", argv[0]);
	printf("service run %s -args \"scan <0 for C, non-zero for Asm>\"\n", argv[0]);
	printf("service run %s -args \"leds <n of elements> <elements>\"\n", argv[0]);
	printf("service run %s -args \"timed_scan <number of seconds>\"\n", argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned long ass, vsize, seconds;

	if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
		if (argc != 3) {
			printf("scan: wrong no. of arguments for kbd_test_scan()\n");
			return 1;
		}
		ass = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (ass == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_scan(%lu)\n", ass);
		return kbd_test_scan(ass);
	}
	else if (strncmp(argv[1], "leds", strlen("leds")) == 0) {
		if (argc < 3) {
			printf("leds: wrong no. of arguments for kbd_test_leds()\n");
			return 1;
		}
		vsize = parse_ulong(argv[2], 10);					/* Parses string to unsigned long */
		if (vsize == ULONG_MAX)
			return 1;
		if (vsize > argc - 3 || vsize <= 0)
		{
			printf("Error: invalid size for specified array\n");
			return 1;
		}

		unsigned short* array;
		array = (unsigned short*) malloc(vsize);

		unsigned short iter = 3;
		while (iter < argc)
		{
			unsigned long element = parse_ulong(argv[iter], 10);
			if (element != ULONG_MAX)
			{
				array[iter - 3] = element;
				iter++;
			}
			else
			{
				printf("leds: %s is not a valid input\n", argv[iter]);
				return 1;
			}
		}

		printf("test3::kbd_test_leds\n");
		return kbd_test_leds(vsize, array);
	}
	else if (strncmp(argv[1], "timed_scan", strlen("timed_scan")) == 0) {
		if (argc != 3) {
			printf("timed_scan: wrong no of arguments for kbd_test_timed_scan()\n");
			return 1;
		}
		seconds = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (seconds == ULONG_MAX)
			return 1;
		printf("test3::kbd_test_timed_scan(%lu)\n", seconds);
		return kbd_test_timed_scan(seconds);
	}
	else {
		printf("test3: %s - no valid function!\n", argv[1]);
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
		printf("test3: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
