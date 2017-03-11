#ifndef __ASTEROID_H
#define __ASTEROID_H

/** @defgroup asteroid asteroid
 * @{
 *
 * Contains the Asteroid struct and functions that manipulate it
 */

#define ALIVE 1	/**< @brief asteroid is alive */
#define DEAD 0	/**< @brief asteroid is dead */

#define TRUE 1	/**< @brief boolean true */
#define FALSE 0 /**< @brief boolean false */

#define ASTEROID_START_DX 4	/**< @brief asteroid starting dx */
#define ASTEROID_START_DY 4	/**< @brief asteroid starting dy */
#define ASTEROID_DEFAULT_DX 0 /**<@brief asteroid default dx */
#define ASTEROID_DEFAULT_DY 0 /**<@brief asteroid default dy */
#define ASTEROID_VX 1		/**< @brief asteroid velocity in x */
#define ASTEROID_VY 1		/**< @brief asteroid velocity in y */

#define ASTEROID_BITMAPS 29 /**<@brief number of bitmaps for asteroid sprite */

#define N_OF_BORDERS 3	/**<@brief number of different spawning borders */

#include "Sprite.h"
#include "Bitmap.h"
#include "Graphics.h"
#include "Asterinix.h"

/** @name Asteroid*/
/**@{
 *
 * @brief Struct with a sprite for an asteroid and its movement parameters
 */
typedef struct {
	int alive;	/**< @brief flag that tells if asteroid is alive*/
	MutableSprite* sprite;		/**< @brief asteroid sprite*/
	int moveLeft;		/**< @brief flag that tells if asteroid should move left*/
	int moveRight;	/**< @brief flag that tells if asteroid should move right*/
	int moveUp;	/**< @brief flag that tells if asteroid should move up*/
	int moveDown;	/**< @brief flag that tells if asteroid should move down*/
	double dx;		/**< @brief displacement in x*/
	double dy;		/**< @brief displacement in y*/
} Asteroid;
/** @} end of Asteroid */

/**
 * @brief Creates an Asteroid object
 * @param asterinix an Asterinix pointer to access bitmaps
 * @return Pointer to an initialized Asteroid object
 */
Asteroid* createAsteroid(Asterinix* asterinix);

/**
 * @brief Sets an asteroid to move left
 * @param asteroid the asteroid to update
 */
void asteroidMoveLeft(Asteroid* asteroid);

/**
 * @brief Sets an asteroid to move right
 * @param asteroid the asteroid to update
 */
void asteroidMoveRight(Asteroid* asteroid);

/**
 * @brief Sets an asteroid to move up
 * @param asteroid the asteroid to update
 */
void asteroidMoveUp(Asteroid* asteroid);

/**
 * @brief Sets an asteroid to move down
 * @param asteroid the asteroid to update
 */
void asteroidMoveDown(Asteroid* asteroid);

/**
 * @brief Clears all movement settings of an asteroid
 * @param asteroid the asteroid to update
 */
void asteroidClearAllFlags(Asteroid* asteroid);

/**
 * @brief Updates the movement and the life status of an asteroid
 * @param asteroid the asteroid to update
 */
void updateAsteroid(Asteroid* asteroid, double dt);

/**
 * @brief Creates an asteroid sprite
 * @param bitmaps an array of bitmap pointers (asteroid bitmap + 28 explosion bitmaps)
 * @return pointer to initialized MutableSprite object
 */
MutableSprite* createAsteroidSprite(Bitmap** bitmaps);

/**
 * @brief Draws an asteroid
 * @param asteroid the asteroid to be drawn
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
void drawAsteroid(Asteroid* asteroid, char transparency, short trColor);

/**
 * @brief Generates a random position on the left, right and bottom sides of the screen
 * @param asteroid_height the height of an asteroid
 * @param asteroid_length the length of an asteroid
 * @return a coordinate of type Coord with the randomly generated position
 */
Coord generateRandomCoord(int asteroid_height, int asteroid_width);

/**
 * @brief Tells if an asteroid is off screen
 * @param asteroid the asteroid to evaluate
 * @return 1 if it is off screen, 0 otherwise
 */
int asteroidOutOfMap(Asteroid* asteroid);

/**@}*/
#endif
