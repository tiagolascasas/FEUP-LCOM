#ifndef __UART_H
#define __UART_H

/** @defgroup asteroid asteroid
 * @{
 *
 * Contains functions to work with the serial port
 */

/**
 * @brief Subscribes serial port interruptions
 * @param com the serial port to be subscripted
 * @return serial port interruption subscription
 */
int uart_subscribe_int(unsigned short com);

/**
 * @brief Unsubscribes serial port interruptions
 * @param com the serial port to be unsubscripted
 * @return 1 if unsuccessfull, 0 otherwise
 */
int uart_unsubscribe_int(unsigned short com);

/**
 * @brief Writes a command to a serial port and its address
 * @param arg the command to be written
 * @param port the serial port
 * @param addr the register to write to
 * @return 1 if unsuccessful, 0 otherwise
 */
int uart_write(short arg, unsigned short port, unsigned char addr);

/**
 * @brief Reads a byte from a register
 * @param port the serial port ro read from
 * @param addr the register to read from
 * @return 0 if unsuccessful, the read value otherwise
 */
char uart_read(unsigned short port, unsigned char addr);

/**
 * @brief Sends a byte through a serial port
 * @param port port to send the byte to
 * @param byte the byte to be sent
 * @return 0 if successful, 1 otherwise
 */
int uart_send_byte(unsigned short port, char byte);

/**
 * @brief Enables serial port interruptions
 * @return 0 if successful, 1 otherwise
 */
int uart_enable_int();

/**
 * @brief Cleans any pending bytes in serial port COM1
 */
void uart_clean();

/**@}*/
#endif /*__UART_H*/
