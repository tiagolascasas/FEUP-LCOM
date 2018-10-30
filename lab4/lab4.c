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

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
}

static void print_usage(char **argv)
{
	printf("%s usage:\n", argv[0]);
	printf("service run %s -args \"packet <n of packets>\"\n", argv[0]);
	printf("service run %s -args \"async <n of seconds>\"\n", argv[0]);
	printf("service run %s -args \"config\"\n", argv[0]);
	printf("service run %s -args \"gesture <length>\"\n", argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned long npacket, nseconds;
	long length;

	if (strncmp(argv[1], "packet", strlen("packet")) == 0) {
		if (argc != 3) {
			printf("packet: wrong no. of arguments for test_packet()\n");
			return 1;
		}
		npacket = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (npacket== ULONG_MAX)
			return 1;
		printf("test4::test_packet(%lu)\n", npacket);
		return test_packet(npacket);
	}
	else if (strncmp(argv[1], "async", strlen("async")) == 0) {
		if (argc != 3) {
			printf("async: wrong no. of arguments for test_async()\n");
			return 1;
		}
		nseconds = parse_ulong(argv[2], 10);					/* Parses string to unsigned long */
		if (nseconds== ULONG_MAX)
			return 1;
		printf("test4::test_async(%lu)\n", nseconds);
		return test_async(nseconds);
	}
	else if (strncmp(argv[1], "config", strlen("config")) == 0){
		if (argc != 2) {
			printf("config: wrong no. of arguments for test_config()\n");
			return 1;
		}
		printf("test4::test_config()\n");
		return test_config(nseconds);
	}
	else if (strncmp(argv[1], "gesture", strlen("gesture")) == 0) {
		if (argc != 3) {
			printf("gesture: wrong no of arguments for test_gesture()\n");
			return 1;
		}
		length = atoi(argv[2]);
		printf("test4::test_gesture(%d)\n", length);
		return test_gesture(length);
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
