#ifndef __RTC_H
#define __RTC_H

/** @defgroup rtc rtc
 * @{
 *
 * Functions to configure and interact with the RTC
 */

/**
 * @brief Writes a byte to RTC
 * @param address the address of the register to write to
 * @param info the byte to be written
 * @return 0 if successful, -1 otherwise
 */
int rtc_write(int address, char info);

/**
 * @brief Disables interruptions
 */
inline void rtc_disable_interrupts();

/**
 * @brief Enables interruptions
 */
inline void rtc_enable_interrupts();

/**
 * @brief Fills an array with the current date and time values
 * @param date the array to be filled
 * @return 1 if unsuccessful, 0 otherwise
 */
int rtc_get_date_and_time(char* date);

/**@}*/
#endif
