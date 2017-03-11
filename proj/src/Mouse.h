#ifndef __MOUSE_H
#define __MOUSE_H

/** @defgroup mouse mouse
 * @{
 *
 * Provides an interface to access the PS/2 mouse and a struct with the mouse pointer status
 */

#include "mouse_defs.h"
#include "i8042.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "Bitmap.h"

#define MOUSE_START_X 504	/**< @brief mouse starting x */
#define MOUSE_START_Y 378	/**< @brief mouse starting y */

/**
 * @brief Subscribes mouse interruptions
 * @return mouse interruption subscription
 */
int mouse_subscribe_int(void);

/**
 * @brief Unsubscribes mouse interruptions
 * @return 1 if unsuccessfull, 0 otherwise
 */
int mouse_unsubscribe_int(void);

/**
 * @brief Writes a command to mouse
 * @param command the command to be written
 * @param port the port to write the command to
 * @return -1 if unsuccessful, 0 otherwise
 */
int mouse_writeCMD(unsigned char command, unsigned short port);

/**
 * @brief Writes a command and its arguments to mouse
 * @param command the command to be written
 * @param hasArgs tells if the command has args or not
 * @param the argument to the command
 * @return -1 if unsuccessful, 0 otherwise
 */
int mouse_write(unsigned char kbc_command, unsigned char ps2_command, char hasArgs, unsigned char argument);

/**
 * @brief Reads a byte from the mouse output buffer
 * @return -1 if unsuccessful, the read value otherwise
 */
unsigned char mouse_read();

/**
 * @brief Joins a 8-bit number with a sign into a 16-bit number
 * @param sign the sign of the new number
 * @param number the 8-bit number
 * @return the new 16-bit number
 */
signed short mouse_join_sig_and_number(char sign, unsigned char number);

/** @name Mouse*/
/**@{
 *
 * @brief Struct with the mouse button and position, its bitmap and current packets
 */
typedef struct {
	Bitmap* pointer;	/**< @brief bitmap for mouse pointer*/
	char leftPressed;	/**< @brief flag that tells if left button is pressed*/
	char rightPressed;	/**< @brief flag that tells if right button is pressed*/
	char middlePressed;	/**< @brief flag that tells if middle button is pressed*/
	int x;				/**< @brief current x position*/
	int y;				/**< @brief current y position*/
	unsigned char packet[3];	/**< @brief current 3-byte packet*/
	char nextPacket;	/**< @brief index of next expected byte of packet*/
} Mouse;
/** @} end of Mouse */

/**
 * @brief Creates a Mouse object
 * @param pointer the bitmap of the mouse pointer
 * @return Pointer to an initialized Mouse object
 */
Mouse* createMouse(Bitmap* pointer);

/**
 * @brief Updates a mouse with a 1-byte packet
 * @param mouse the mouse to be updated
 * @param packet the 1-byte packet
 */
void updateMouse(Mouse* mouse, unsigned char packet);

/**
 * @brief Draws a mouse at its current position
 * @param mouse the mouse to be drawn
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
void drawMouse(Mouse* mouse, char transparency, short trColor);

/**
 * @brief Updates the mouse position based on a complete 3-byte packet
 * @param mouse the mouse to be updated
 */
void updateMouseMoves(Mouse* mouse);

/**
 * @brief Updates the mouse button status based on a complete 3-byte packet
 * @param mouse the mouse to be updated
 */
void updateMouseButtons(Mouse* mouse);

/**@}*/
#endif /* __MOUSE_H */
