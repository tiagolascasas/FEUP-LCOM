#ifndef __TIMER_H
#define __TIMER_H
#include "i8254.h"

/** @defgroup timer timer
 * @{
 *
 * Contains functions to un/subscribe timer interruptions
 */

/**
 * @brief Subscribes timer interruptions
 * @return timer interruption subscription
 */
int timer_subscribe_int(void );

/**
 * @brief Unsubscribes timer interruptions
 * @return 1 if unsuccessfull, 0 otherwise
 */
int timer_unsubscribe_int();

/**@}*/
#endif /* __TIMER_H */
