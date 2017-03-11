#ifndef __MOUSE_DEFS_H
#define __MOUSE_DEFS_H

/** @defgroup mouse_defs mouse_defs
 * @{
 *
 * Constants to configure and work with the PS/2 mouse
 */

/*interruptions-related codes*/
#define MOUSE_IRQ 12	/**< @brief mouse irq */
#define HOOK_ID_3 3		/**< @brief hookid for mouse */

/*ports*/
#define CTRL_REG 0x64		/**< @brief control register port */
#define IN_BUF_MOUSE 0x60	/**< @brief input buffer port */
#define OUT_BUF_MOUSE 0x60	/**< @brief output buffer port */

/*kbc commands*/
#define ENABLE_MOUSE 0xA8	/**< @brief enable mouse command */
#define DISABLE_MOUSE 0xA7	/**< @brief disable mouse command */
#define WRITE_BYTE_TO_MOUSE 0xD4	/**< @brief write byte to mouse command */
#define READ_BYTE 0x20		/**< @brief read byte command */
#define WRITE_BYTE 0x60		/**< @brief write byte command */

/*ps2 commands*/
#define STREAM_MODE 0xEA	/**< @brief enable stream mode */
#define DISABLE_DATA_REP 0xF5	/**< @brief disable data reporting */
#define ENABLE_DATA_REP 0xF4	/**< @brief enable data reporting */
#define STATUS_REQUEST 0xE9		/**< @brief status request */

/*acknowledgement codes*/
#define ACK 0xFA		/**< @brief acknoweldged code */
#define NACK 0xFE		/**< @brief not acnkowledged code */
#define ERROR 0xFC		/**< @brief error code */

/*miscellaneous*/
#define NO_ARG 0x0		/**< @brief no arguments */
#define SIGN_1 0xff00	/**< @brief signed short */
#define SIGN_0 0x0		/**< @brief unsigned short */
#define READ_ERROR 0x0	/**< @brief reading error */

/**@}*/
#endif /*__MOUSE_DEFS_H*/
