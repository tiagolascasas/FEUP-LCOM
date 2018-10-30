#include <string.h>
#include <errno.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "pixmap.h"

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
	printf("service run %s -args \"init <mode (hex)> <delay>\"\n", argv[0]);
	printf("service run %s -args \"square <x> <y> <size> <color (hex)>\"\n", argv[0]);
	printf("service run %s -args \"line <xi> <yi> <xf> <yf> <color (hex)>\"\n", argv[0]);
	printf("service run %s -args \"xpm <xi> <yi> <xpm picture>\"\n", argv[0]);
	printf("service run %s -args \"move <xi> <yi> <xpm picture> <0 for vertical, non-zero for horizontal> <length in pixels> <duration>\"\n", argv[0]);
	printf("service run %s -args \"controller\"\n", argv[0]);
}

static int proc_args(int argc, char **argv)
{
	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if (argc != 4) {
			printf("init: wrong no. of arguments for test_init()\n");
			return 1;
		}
		unsigned short mode, delay;

		mode = parse_ulong(argv[2], 16);						/* Parses string to unsigned long */
		if (mode == ULONG_MAX)
			return 1;
		delay = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
		if (delay == ULONG_MAX)
			return 1;

		printf("test5::test_init(0x%x, %d)\n", mode, delay);
		return test_init(mode, delay);
	}
	else if (strncmp(argv[1], "square", strlen("square")) == 0) {
		if (argc != 6) {
			printf("square: wrong no. of arguments for test_square()\n");
			return 1;
		}
		unsigned short x, y, size;
		unsigned long color;

		x = parse_ulong(argv[2], 10);					/* Parses string to unsigned long */
		y = parse_ulong(argv[3], 10);
		size = parse_ulong(argv[4], 10);
		color = parse_ulong(argv[5], 16);

		if (x == ULONG_MAX || y == ULONG_MAX || size == ULONG_MAX || color == ULONG_MAX)
			return 1;
		printf("test5::test_square(%d, %d, %d, 0x%x)\n", x, y, size, color);
		return test_square(x, y, size, color);
	}
	else if (strncmp(argv[1], "line", strlen("line")) == 0){
		if (argc != 7) {
			printf("line: wrong no. of arguments for test_line()\n");
			return 1;
		}
		unsigned short xi, yi, xf, yf;
		unsigned long color;

		xi = parse_ulong(argv[2], 10);					/* Parses string to unsigned long */
		yi = parse_ulong(argv[3], 10);
		xf = parse_ulong(argv[4], 10);
		yf = parse_ulong(argv[5], 10);
		color = parse_ulong(argv[6], 16);

		if (xi == ULONG_MAX || yi == ULONG_MAX || xf == ULONG_MAX
							|| yf == ULONG_MAX || color == ULONG_MAX)
			return 1;

		printf("test5::test_line(%d, %d, %d, %d, 0x%x)\n", xi, yi, xf, yf, color);
		return test_line(xi, yi, xf, yf, color);
	}
	else if (strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
		if (argc !=5) {
			printf("xpm: wrong no of arguments for test_xpm()\n");
			return 1;
		}
		unsigned short xi, yi;

		xi = parse_ulong(argv[2], 10);					/* Parses string to unsigned long */
		yi = parse_ulong(argv[3], 10);

		if (strncmp(argv[4], "pic1", strlen("pic1")) == 0)
		{
			printf("test5::test_xpm(%d, %d, \"pic1\")\n", xi, yi);
			return test_xpm(xi, yi, pic1);
		}
		else if (strncmp(argv[4], "pic2", strlen("pic2")) == 0)
		{
			printf("test5::test_xpm(%d, %d, \"pic2\")\n", xi, yi);
			return test_xpm(xi, yi, pic2);
		}
		else if (strncmp(argv[4], "cross", strlen("cross")) == 0)
		{
			printf("test5::test_xpm(%d, %d, \"cross\")\n", xi, yi);
			return test_xpm(xi, yi, cross);
		}
		else if (strncmp(argv[4], "pic3", strlen("pic3")) == 0)
		{
			printf("test5::test_xpm(%d, %d, \"pic3\")\n", xi, yi);
			return test_xpm(xi, yi, pic3);
		}
		else if (strncmp(argv[4], "penguin", strlen("penguin")) == 0)
		{
			printf("test5::test_xpm(%d, %d, \"penguin\")\n", xi, yi);
			return test_xpm(xi, yi, penguin);
		}
		else
		{
			printf("Error: unknown picture name\n");
			return 1;
		}

	}
	else if (strncmp(argv[1], "move", strlen("move")) == 0) {
		if (argc != 8) {
			printf("move: wrong no of arguments for test_move()\n");
			return 1;
		}
		unsigned short xi, yi, hor, time;
		short delta;

		xi = parse_ulong(argv[2], 10);					/* Parses string to unsigned long */
		yi = parse_ulong(argv[3], 10);
		hor = parse_ulong(argv[5], 10);
		delta = atoi(argv[6]);
		time = parse_ulong(argv[7], 10);

		if (xi == ULONG_MAX || yi == ULONG_MAX || hor == ULONG_MAX || time == ULONG_MAX)
			return 1;

		if (strncmp(argv[4], "pic1", strlen("pic1")) == 0)
		{
			printf("test5::test_move(%d, %d, \"pic1\", %d, %d, %d)\n", xi, yi, hor, delta, time);
			return test_move(xi, yi, pic1, hor, delta, time);
		}
		else if (strncmp(argv[4], "pic2", strlen("pic2")) == 0)
		{
			printf("test5::test_move(%d, %d, \"pic2\", %d, %d, %d)\n", xi, yi, hor, delta, time);
			return test_move(xi, yi, pic2, hor, delta, time);
		}
		else if (strncmp(argv[4], "cross", strlen("cross")) == 0)
		{
			printf("test5::test_move(%d, %d, \"cross\", %d, %d, %d)\n", xi, yi, hor, delta, time);
			return test_move(xi, yi, cross, hor, delta, time);
		}
		else if (strncmp(argv[4], "pic3", strlen("pic3")) == 0)
		{
			printf("test5::test_move(%d, %d, \"pic3\", %d, %d, %d)\n", xi, yi, hor, delta, time);
			return test_move(xi, yi, pic3, hor, delta, time);
		}
		else if (strncmp(argv[4], "penguin", strlen("penguin")) == 0)
		{
			printf("test5::test_move(%d, %d, \"penguin\", %d, %d, %d)\n", xi, yi, hor, delta, time);
			return test_move(xi, yi, penguin, hor, delta, time);
		}
		else
		{
			printf("Error: unknown picture name\n");
			return 1;
		}
	}
	else if (strncmp(argv[1], "controller", strlen("controller")) == 0){
		if (argc != 2) {
			printf("controller: wrong no. of arguments for test_controller()\n");
			return 1;
		}
		printf("test5::test_controller())\n");
		return test_controller();
	}
	else {
		printf("test5: %s - no valid function!\n", argv[1]);
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
		printf("test5: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
