#ifndef __GAME_H
#define __GAME_H

#include "Player.h"
#include "Stage.h"
#include "Asterinix.h"
#include "Score.h"
#include "Highscores.h"
#include "UART.h"

/** @defgroup game game
 * @{
 *
 * Main game module
 */

#define RUNNING 1	/**< @brief game is running */
#define OVER 0		/**< @brief game is not running */
#define LIVES_3 3	/**< @brief 3 lives */
#define LIVES_2 2	/**< @brief 2 lives */
#define LIVES_1 1	/**< @brief 1 life */
#define LIVES_0 0	/**< @brief 0 lives */
#define DEFAULT_DT 1	/**< @brief default time variation */
#define DEF_VT 0		/**< @brief default velocity */
#define SET_TICK 1		/**< @brief timer interruption */
#define RESET_TICK 0	/**< @brief reset timer interruption indicator */
#define SECOND 60		/**< @brief number of timer ticks in 1 second */
#define NULL_TIME 0		/**< @brief time zero */
#define FIRST_FRAME 1	/**< @brief first frame */
#define NULL_SCORE 0	/**< @brief score zero */
#define BUTTON_BITMAPS 2	/**< @brief number of bitmaps in a button */
#define NULL_RESPONSE '.'	/**< @brief default response for when no byte is read from serial port */

/** @name Game*/
/**@{
 *
 * @brief Struct with the game status
 *
 * It includes the current stage, the player,
 * the score, the highscores table and the menu buttons,
 * as well as multiplayer-related flags
 */
typedef struct {
	Player* player;		/**< @brief player*/
	int running;		/**< @brief flag that tells if the game is running or not*/
	Stage* stage;		/**< @brief current stage*/
	MutableSprite* livesSprite;		/**< @brief sprite for lives*/
	Sprite* asterLogo;		/**< @brief sprite for the asterinix main menu logo*/
	MutableSprite* singleplayerButton;		/**< @brief sprite for singleplayer button*/
	MutableSprite* multiplayerButton;		/**< @brief sprite for multiplayer button*/
	MutableSprite* highscoresButton;		/**< @brief sprite for highscores button*/
	MutableSprite* howtoplayButton;			/**< @brief sprite for howtoplay button*/
	MutableSprite* exitgameButton;			/**< @brief sprite for exit button*/
	MutableSprite* backButton;				/**< @brief sprite for back button*/
	MutableSprite* resetButton;				/**< @brief sprite for reset button*/
	Score* score;						/**< @brief score object*/
	HighscoreTable* hsTable;			/**< @brief highscore table*/
	int connecting;						/**< @brief flag that tells if the game is connecting to multiplayer*/
	char playMultiplayer;				/**< @brief flag that tells if the game is ready to begin a MP match*/
} Game;
/** @} end of Game */

/**
 * @brief Creates a Game object
 * @param asterinix an Asterinix pointer to access bitmaps
 * @return Pointer to an initialized Game object
 */
Game* createGame(Asterinix* asterinix);

/**
 * @brief Main game loop, calling update input, update game and draw functions
 * @param game a Game pointer to access game status
 * @param asterinix an Asterinix pointer to access bitmaps
 */
void play(Game* game, Asterinix* asterinix);

/**
 * @brief Processes interruptions, calling their respective handlers
 * @param game a Game pointer to access the timer status
 * @param asterinix an Asterinix pointer to access interruption subscriptions and the keyboard/mouse status
 */
void updateInput(Game* game, Asterinix* asterinix);

/**
 * @brief Draws the current stage, the mouse and implements the double-buffering
 * @param game a Game pointer to access the current stage
 * @param asterinix an Asterinix pointer to access bitmaps
 */
void draw(Game* game, Asterinix* asterinix);

/**
 * @brief Updates the current stage, changing stage if required
 * @param game a Game pointer with the current stage
 * @param asterinix an Asterinix pointer to access bitmaps and the mouse
 */
void updateGame(Game* game, Asterinix* asterinix, double dt);

/**
 * @brief Checks if the mouse is hovering and/or pressing any of the menu buttons, and updates the game status according to it
 * @param game a Game pointer to access the game status
 * @param asterinix an Asterinix pointer to access bitmaps and the mouse
 */
void checkMenuButtons(Game* game, Asterinix* asterinix);

/**
 * @brief Checks if the mouse is hovering and/or pressing any of the highscores buttons, and updates the game status according to it
 * @param game a Game pointer to access the game status
 * @param asterinix an Asterinix pointer to access bitmaps and the mouse
 */
int checkHighscoreButtons(Game* game, Asterinix* asterinix);

/**
 * @brief Sends a byte through serial port COM1
 * @param byte the byte to be sent
 */
void send_byte(char byte);

/**
 * @brief Checks if there is a byte to be received in COM1, and if so reads and returns it
 * @return char '.' if there wasn't anything to be read, or the character that was received otherwise
 */
char receive_byte_poll();

/**@}*/
#endif
