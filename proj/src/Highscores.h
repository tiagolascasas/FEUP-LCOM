#ifndef __HIGHSCORES_H
#define __HIGHSCORES_H

#include "Sprite.h"
#include "Asterinix.h"

/** @defgroup highscores highscores
 * @{
 *
 * Contains structs and functions that implement an highscore table
 */

#define MAX_HS 9		/**< @brief maximum size of highscore table */
#define ASCTIME_SIZE 24	/**< @brief number of chars in an asctime string */
#define MAX_ALGARISMS 5	/**< @brief maximum number of score algarisms */
#define BASE 10			/**< @brief numerical base in which the score is set */
#define X_INC 17		/**< @brief increment factor for x */
#define Y_INC 44		/**< @brief increment factor for y */
#define Y_CORRECTION 11	/**< @brief correction factor for y */
#define X_START_RANK 17	/**< @brief starting position for rank in x */
#define X_START_SCORE 71 + X_INC * MAX_ALGARISMS	/**< @brief  starting position for score in x */
#define X_START_TIME 189	/**< @brief starting position for time in x */
#define DEFAULT_TIME "         empty         "	/**< @brief default time string */
#define DEFAULT_SCORE 0				/**< @brief default score */
#define SAVE "/save/highscores.txt"	/**< @brief relative path of save file */
#define SUCCESS 0					/**< @brief added score with success */
#define INSUCCESS 1					/**< @brief didn't add score with success */
#define LOAD_BUFFER_SIZE 30			/**< @brief input buffer size for file read */
#define SAVE_BUFFER_SIZE 7			/**< @brief output buffer size for file write */

/** @name Highscore*/
/**@{
 *
 * @brief Struct with a sprite for a highscore, a timestamp and a score
 */
typedef struct {
	Bitmap* background;	/**< @brief background for a score*/
	char timestamp[ASCTIME_SIZE];	/**< @brief UNIX timestamp string*/
	unsigned int score;				/**< @brief score value*/
} Highscore;
/** @} end of Highscore */

/** @name HighscoreTable*/

/**@{
 *
 * @brief Struct with an array of highscores
 */
typedef struct {
	Highscore* table[MAX_HS];	/**< @brief array of highscores*/
} HighscoreTable;
/** @} end of HighscoreTable */

/**
 * @brief Creates a new Highscore
 * @param background the highscore background
 * @param timestamp a 24-byte string with a timestamp
 * @param score the score
 * @return pointer to initialized Highscore object
 */
Highscore* createHighscore(Bitmap* background, char* timestamp, unsigned int score);

/**
 * @brief Draws a Highscore
 * @param highscore the highscore to be drawn
 * @param x the x coordinate of the highscore
 * @param y the y coordinate of the highscore
 * @param font the font to draw the score
 * @param rank the position of the highscore on the highscore table
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
void drawHighscore(Highscore* highscore, int x, int y, Font* font, int rank, char transparency,
																				short trColor);
/**
 * @brief Compares two highscores, to be used as an argument to qsort()
 * @param h1 a void pointer to the first highscore
 * @param h2 a void pointer to the second highscore
 * @return -1 if h1 > h2, 0 if h1 == h2, 1 if h1 < h2
 */
int compareHighscores(const void* h1, const void* h2);

/**
 * @brief Creates a Highscore Table
 * @param highscores an array of Highscore pointers
 * @return pointer to initialized HighscoreTable object
 */
HighscoreTable* createHighscoreTable(Highscore** highscores);

/**
 * @brief Draws a Highscore Table
 * @param hsTable the highscore table to be drawn
 * @param x the x coordinate of the highscore
 * @param y the y coordinate of the highscore
 * @param font the font to draw the score
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
void drawHighscoreTable(HighscoreTable* hsTable, int x, int y, Font* font, char transparency,
																			short trColor);
/**
 * @brief Tries to add an highscore to the highscore table, reporting in/success, and rearranges the table
 * @param hsTable the highscore table
 * @param highscore to be added
 * @return 0 if successful, 1 if not
 */
int addHighscore(HighscoreTable* hsTable, Highscore* highscore);

/**
 * @brief Resets all highscores in a highscore table
 * @param hsTable the highscore table

 */
void resetHighscores(HighscoreTable* hsTable);

/**
 * @brief Reads highscores from a file and fills an array with them
 * @param highscores the array to be filled
 * @param asterinix a pointer to an Asterinix object to access bitmaps and path
 */
void readHighscores(Highscore** highscores, Asterinix* asterinix);

/**
 * @brief Saves the highscores on a table to a file
 * @param hsTable the highscores table
 * @param asterinix a pointer to an Asterinix object to access bitmaps and path
 */
void saveHighscores(HighscoreTable* hsTable, Asterinix* asterinix);

/**@}*/
#endif /*__HIGHSCORES*/
