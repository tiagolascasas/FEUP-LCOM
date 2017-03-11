#ifndef __STAGE_H
#define __STAGE_H

/** @defgroup player player
 * @{
 *
 * Contains the struct player and functions that manipulate it
 */

#define MAX_ASTEROIDS 20		/**< @brief maximum number of asteroids on screen */
#define ASTEROID_SPAWN_TRIGGER 15	/* number of timer ticks in a quarter of a second*/

#define FINISHED 1		/**< @brief stage is finished */
#define UNFINISHED 0	/**< @brief stage is unfinished */

#define DEFAULT_LIVES 3	/**< @brief number of player lives */

#include "Asterinix.h"
#include "Asteroid.h"
#include "Bitmap.h"
#include "Player.h"
#include "Bullet.h"

/** @name Stagetype*/
/**@{
 *
 * Enumeration with all the different stage types
 */
typedef enum {
	MENU,
	SINGLE,
	MULTI,
	HIGH,
	HOW
} Stagetype;
/** @} end of Stagetype */

/** @name Stage*/
/**@{
 *
 * @brief Struct with the status of the current stage
 */
typedef struct {
	Asteroid* mobs[MAX_ASTEROIDS];	/**< @brief array of asteroids*/
	int current_asteroids;			/**< @brief current number of asteroids*/
	int time;					/**< @brief time counter of stage*/
	int finished;				/**< @brief flag that tells if the stage is finished*/
	int exit_game;				/**< @brief flag that tells that the game must exit*/
	Stagetype stagetype;		/**< @brief type of current stage*/
	Stagetype nextStage;		/**< @brief type of next stage*/
	Bitmap* currentGameOver;	/**< @brief game over bitmap*/
	int addedHighscore;			/**< @brief flag that tells if a highscore has just been added*/
	MutableSprite* livesSprite;	/**< @brief sprite for the lives of a player*/
} Stage;
/** @} end of Stage*/

/**
 * @brief Creates a Stage object
 * @param st the type of stage
 * @asterinix pointer to Asterinix object to access bitmaps
 * @return Pointer to an initialized Stage object
 */
Stage* createStage(Stagetype st, Asterinix* asterinix);

/**
 * @brief Updates a stage
 * @param stage the current stage
 * @param dt time interval for movement update
 * @param asterinix pointer to Asterinix object to access bitmaps and mouse/keyboard status
 */
void updateStage(Stage* stage, double dt, Asterinix* asterinix);

/**
 * @brief Checks collisions between the player and asteroids
 * @param player the Player
 * @param stage the current Stage with the asteroids
 * @return the number of collisions
 */
int checkCollisions(Player* player, Stage* stage);

/**
 * @brief Checks if a Player is colliding with an Asteroid
 * @param player the Player
 * @param asteroid the Asteroid
 * @return 1 if it is collididing, 0 otherwise
 */
int colliding(Player* player, Asteroid* asteroid);

/**
 * @brief Checks collisions between all bullets and all asteroids
 * @param player the Player with all the Bullets
 * @param stage the current Stage with all the Asteroids
 * @return number of collisions
 */
int checkBulletsCollisions(Player* player, Stage* stage);

/**
 * @brief Checks if a Bullet is colliding with an Asteroid
 * @param asteroid the Asteroid
 * @param bullet the Bullet
 * @return 1 if it is colliding, 0 otherwise
 */
int bulletColliding(Asteroid* asteroid, Bullet* bullet);

/**@}*/
#endif
