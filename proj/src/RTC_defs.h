#ifndef __RTC_DEFS_H
#define __RTC_DEFS_H

/** @defgroup rtc_defs rtc_defs
 * @{
 *
 * Constants to configure and work with the RTC
 */

/*ports*/

#define RTC_ADDR_REG 0x70	/**< @brief address register port */
#define RTC_DATA_REG 0x71	/**< @brief data register port */

/*registers*/

#define SECONDS 0	/**< @brief seconds register address */
#define MINUTES 2	/**< @brief minutes register address */
#define HOURS 4		/**< @brief hours register address */
#define DAY 7		/**< @brief day register address */
#define MONTH 8		/**< @brief month register address */
#define YEAR 9		/**< @brief year register address */
#define REG_A 10	/**< @brief register A address */
#define REG_B 11	/**< @brief register B address */

/*configuration*/

#define CONF 0b00000110 	/**< @brief enable 24h binary format */
#define BIT(n) (0x01<<(n))

/**@}*/
#endif /*__RTC_DEFS_H*/

