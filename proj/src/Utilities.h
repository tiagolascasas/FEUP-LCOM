#ifndef __UTILITIES_H
#define __UTILITIES_H

#include <time.h>

/** @defgroup asteroid asteroid
 * @{
 *
 * Utilitary functions
 */

#define CENTURY 100		/**< @brief number of years in a century */
#define MONTH_CORRECTION 1	/**< @brief correction factor for month */

/**
 * @brief Cleans keyboard/mouse output buffer and unsubscribes interruptions from timer, keyboard and mouse
 * @return 1 if unsuccessful, 0 otherwise
 */
int unsubscribe_all();

/**
 * @brief Creates a full path for a file from a relative one
 * @param path the path of the binary passed as an argument to main
 * @param file the relative path of the file
 * @return full path to file
 */
char* makePath(char* path, char* file);

/**
 * @brief Gets a UNIX timestamp from a date-time read from the RTC (equivalent in practise to time(NULL))
 * @return UNIX timestamp of the current time
 */
time_t getCurrentTime();

/**
 * @brief Gets a UNIX timestamp string from a date-time read from the RTC (equivalent in practise to asctime(time(NULL)))
 * @return UNIX timestamp string of the current time
 */
char* getCurrentTimeStr();

/**@}*/
#endif /*__UTILITIES_H*/
