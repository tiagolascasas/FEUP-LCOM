#ifndef __KEYBOARD_H
#define __KEYBOARD_H

/** @defgroup keyboard keyboard
 * @{
 *
 * Provides and interface to access the keyboard and a struct with the pressed keys status
 */

#include "i8042.h"

#define PRESSED 1	/**< @brief key is pressed */
#define RELEASED 0	/**< @brief key is released */
#define TWO_BYTE_YES 1	/**< @brief dealing with two byte scancode */
#define TWO_BYTE_NO 0	/**< @brief dealing with one byte scancode */

/**
 * @brief Subscribes keyboard interruptions
 * @return keyboard interruption subscription
 */
int kbd_subscribe_int(void);

/**
 * @brief Unsubscribes keyboard interruptions
 * @return 1 if unsuccessfull, 0 otherwise
 */
int kbd_unsubscribe_int(void);

/**
 * @brief Writes a command to keyboard output buffer
 * @param command the command to be written
 * @return -1 if unsuccessful, 0 otherwise
 */
int kbd_writeCMD(char command);

/**
 * @brief Writes a command with its argument to the keyboard output buffer
 * @param command the command to be written
 * @param argument the argument of the command
 * @return -1 if unsuccessful, 0 otherwise
 */
int kbd_write(char command, char argument);

/**
 * @brief Creates a 2-byte scancode from the LSB of one
 * @param scancode the LSB of a 2-byte scancode
 * @return a 2-byte scancode
 */
unsigned short kbd_make_2byte_scancode(unsigned char scancode);

/** @name key_status_t*/
/**@{
 *
 * @brief Struct with the keys status (pressed/released)
 *
 * It includes a flag for every key used in the game, plus
 * a flag that tells if a certain scancode is the MSB of
 * a two-byte scancode
 */
typedef struct {
	char key_w;	/**< @brief w key*/
	char key_a;	/**< @brief a key*/
	char key_s;	/**< @brief s key*/
	char key_d;	/**< @brief d key*/
	char key_arrow_up;		/**< @brief arrow up key*/
	char key_arrow_down;	/**< @brief arrow down key*/
	char key_arrow_left;	/**< @brief arrow left key*/
	char key_arrow_right;	/**< @brief arrow right key*/
	char key_esc;	/**< @brief esc key*/
	char key_enter;	/**< @brief enter key*/
	char two_byte;	/**< @brief tells if the scancode was a two-byte indicator*/
} key_status_t;
/** @} end of key_status_t */

/** @name scancode*/
/**@{
 *
 * @brief Enumeration of the make and break codes of the keys in key_status_t
 */
typedef enum {
	MAKE_W =	0x11,
	BREAK_W	=	0x91,
	MAKE_A =	0x1e,
	BREAK_A	=	0x9e,
	MAKE_S =	0x1f,
	BREAK_S	=	0x9f,
	MAKE_D=		0x20,
	BREAK_D	=	0xa0,

	MAKE_ARROW_UP =		0xe048,
	BREAK_ARROW_UP =	0xe0c8,
	MAKE_ARROW_LEFT	=	0xe04b,
	BREAK_ARROW_LEFT =	0xe0cb,
	MAKE_ARROW_DOWN =	0xe050,
	BREAK_ARROW_DOWN =	0xe0d0,
	MAKE_ARROW_RIGHT =	0xe04d,
	BREAK_ARROW_RIGHT = 0xe0cd,

	MAKE_ESC =	0x01,
	BREAK_ESC =	0x81,

	MAKE_ENTER = 0x1c,
	BREAK_ENTER = 0x9c,

	TWO_BYTE_INDICATOR = 0xE0
} scancode;
/** @} end of scancode */

/**
 * @brief Creates a key_status_t object
 * @return Pointer to an initialized key_status_t object
 */
key_status_t* createKeyStatus();

/**
 * @brief Updates a key_status_t object with a single one-byte scancode
 * @param key_status the key_status_t object to be updated
 * @param scancode the scancode to be added
 */
void updateKeyStatus(key_status_t* key_status, scancode sc);

/**@}*/
#endif /* __KEYBOARD_H */
