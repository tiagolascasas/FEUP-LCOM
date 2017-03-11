#ifndef __i8042_H
#define __i8042_H

/** @defgroup i8042 i8042
 * @{
 *
 * Constants to configure and work with the i8042 PS/2 keyboard standard
 */
#define BIT(n) (0x01<<(n))

#define BITS_IN_CHAR 8

#define TIMER0_IRQ                0    /**< @brief Timer 0 IRQ line */

#define KBD_IRQ 1			/**< @brief keybard irq */
#define HOOK_ID_2 2			/**< @brief hook_id for keyboard */

#define STAT_REG 0x64		/**< @brief status register port*/
#define IN_BUF 0x20			/**< @brief input buffer port */
#define OUT_BUF 0x60		/**< @brief output buffer port */

#define PAR BIT(7)			/**< @brief parity */
#define TIMEOUT BIT(6)		/**< @brief timeout */
#define IBF BIT(1)			/**< @brief input buffer full */
#define OBF BIT(0)			/**< @brief outbut buffer full */

#define TWO_BYTE_SCAN_CODE 0xE0	/**< @brief two byte scancode indicator */
#define TWO_BYTE_GENERIC 0xE000	/**< @brief  generic template for two-byte scancode */

#define RETRIES 5		/**< @brief number of retries */

#define SET_LEDS 0xED	/**< @brief set keyboard leds */
#define RESET_AND_ENABLE 0xF6	/**< @brief reset buffers and (re)enable keyboard */

#define DELAY_US 20000	/**< @brief delay in ms */

/**@}*/
#endif /*__i8042_H*/
