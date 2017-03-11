/** @defgroup main main
 * @{
 *
 * Contains the main function
 */

#include "video_defs.h"
#include "lmlib.h"
#include "Asterinix.h"
#include "Game.h"
#include "Utilities.h"
#include "UART.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief Initializes the service, instanciates game and asterinix, changes video mode and unsubscribes peripherals
 * @param argc number of arguments
 * @param argv pointer to strings
 * @return 0 if game exits successfully, 1 otherwise
 */
int main(int argc, char** argv)
{
	sef_startup();
	sys_enable_iop(SELF);

	lm_init();
	vg_init(MODE_RGB_1024X768);

	if (mouse_writeCMD(ENABLE_MOUSE, CTRL_REG) != 0) return 1;								/*enable mouse*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, STREAM_MODE, NO_ARG, NO_ARG) != 0) return 1;		/*set mouse to stream mode*/
	if (mouse_write(WRITE_BYTE_TO_MOUSE, ENABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;	/*set mouse to receive data packets*/

	Asterinix* asterinix = createAsterinix(argv[0]);

	Game* game = createGame(asterinix);

	time_t timestamp = getCurrentTime();	/*get current timestamp using RTC*/
	srand(timestamp);						/*and use it as a seed, with the same effect as time(NULL)*/

	play(game, asterinix);

	if (unsubscribe_all() != 0) return 1;

	if (mouse_write(WRITE_BYTE_TO_MOUSE, DISABLE_DATA_REP, NO_ARG, NO_ARG) != 0) return 1;
	if (mouse_writeCMD(DISABLE_MOUSE, CTRL_REG) != 0) return 1;

	uart_clean();

	vg_exit();

	printf("Asterinix exited successfully\n");

	return 0;
}
