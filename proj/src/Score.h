#ifndef __SCORE_H
#define __SCORE_H

/** @defgroup score score
 * @{
 *
 * Contains a Score struct and functions that manipulate it
 */

#include "Sprite.h"
#include "Asterinix.h"

#define MAX_ALGARISMS 5	/**< @brief maximum algarisms for a score */
#define BASE 10			/**< @brief numerical base of the score */

#define DEFAULT_V 0		/**< @brief default velocity */
#define NULL_SCORE 0	/**< @brief score zero */

#define SCORE_X 823		/**< @brief score starting x */
#define SCORE_Y 0		/**< @brief score starting y */

#define ALG_0_X 1005	/**< @brief algarism 0 of score starting x */
#define ALG_0_Y 5		/**< @brief algarism 0 of score starting y */
#define ALG_1_X 988		/**< @brief algarism 1 of score starting x */
#define ALG_1_Y 5		/**< @brief algarism 1 of score starting y */
#define ALG_2_X 971		/**< @brief algarism 2 of score starting x */
#define ALG_2_Y 5		/**< @brief algarism 2 of score starting y */
#define ALG_3_X 954		/**< @brief algarism 3 of score starting x */
#define ALG_3_Y 5		/**< @brief algarism 3 of score starting y */
#define ALG_4_X 937		/**< @brief algarism 4 of score starting x */
#define ALG_4_Y 5		/**< @brief algarism 4 of score starting y */

/** @name Score*/
/**@{
 *
 * @brief Struct for a score, with its background and number sprites and the score value
 */
typedef struct {
	Sprite* algarisms[MAX_ALGARISMS];	/**< @brief array of sprites with algarisms*/
	int currentScore;					/**< @brief current score value*/
	Sprite* background;					/**< @brief background sprite for the score*/
} Score;
/** @} end of Score */

/**
 * @brief Creates a Score object
 * @param asterinix an Asterinix pointer to access bitmaps
 * @return Pointer to an initialized Score object
 */
Score* createScore(Asterinix* asterinix);

/**
 * @brief Increments a Score by a given value
 * @param score the Score to be incremented
 * @param increment the increment value
 * @param font the Font to update the score with
 */
void incrementScore(Score* score, unsigned int increment, Font* font);

/**
 * @brief Draws a Score
 * @param score the Score to be drawn
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
void drawScore(Score* score, char transparency, short trColor);

/**
 * @brief Resets a score to 0
 * @param score the Score to be reset
 * @param font the Font to update the score with
 */
void resetScore(Score* score, Font* font);

/**@}*/
#endif
