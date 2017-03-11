#ifndef __UARTDEFS_H
#define __UARTDEFS_H

/** @defgroup asteroid asteroid
 * @{
 *
 * Constants to configure and work with the serial port
 */

/*UART ports*/

#define COM1 0x3F8	/**< @brief COM1 address */
#define COM2 0x2F8	/**< @brief COM2 address */

/*UART registers*/

#define RBR 0	/**< @brief receiver buffer register */
#define THR 0	/**< @brief transmitter buffer register */
#define LSR 5	/**< @brief line status register */
#define LCR 3	/**< @brief line control register */
#define DDL 0	/**< @brief divisor latch LSB */
#define DLM 1	/**< @brief divisor latch MSB */
#define IER 1	/**< @brief interrupt enable register */
#define IIR 2	/**< @brief interrupt identification register */
#define FCR 2	/**< @brief FIFO control register */

/*hook id and IRQ*/

#define HOOK_ID_4 4	/**< @brief hookid 4 */
#define HOOK_ID_5 5	/**< @brief hookid 5 */
#define COM1_IRQ 4	/**< @brief COM1 IRQ line */
#define COM2_IRQ 3	/**< @brief COM2 IRQ line */

/*IER configuration*/

#define ENABLE_INT 0b00000011	/**< @brief configuration to enable interrupts */

/*bit manipulation*/

#define BIT(n) (0x01<<(n))

/**@}*/
#endif /*__UARTDEFS_H*/
