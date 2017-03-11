#ifndef __BULLET_H
#define __BULLET_H

#include "Sprite.h"
#include "Keyboard.h"
#include "Graphics.h"

/** @defgroup bullet bullet
 * @{
 *
 * Contains the Bullet struct and functions that manipulate it
 */

#define ALIVE 1	/**< @brief bullet is alive */
#define DEAD 0	/**< @brief bullet is dead */
#define TRUE 1	/**< @brief boolean true */
#define FALSE 0 /**< @brief boolean false */

#define START_X 492			/**< @brief bullet starting x */
#define START_Y 364			/**< @brief bullet starting y */
#define BULLET_START_DX 8	/**< @brief bullet starting dx*/
#define BULLET_START_DY 8	/**< @brief bullet starting dy */
#define DEFAULT_VX 1		/**< @brief bullet default velocity in x */
#define DEFAULT_VY 1		/**< @brief bullet default velocity in y */

#include "Sprite.h"

/** @name Bullet*/
/**@{
 *
 * @brief Struct with a sprite for a bullet and its movement parameters
 */
typedef struct {
	int alive;	/**< @brief flag that tells if the bullet is alive*/
	Sprite* sprite;		/**< @brief bullet sprite*/
	int moveLeft;		/**< @brief flag that tells if the bullet should move left*/
	int moveRight;		/**< @brief flag that tells if the bullet should move right*/
	int moveUp;			/**< @brief flag that tells if the bullet should move up*/
	int moveDown;		/**< @brief flag that tells if the bullet should move down*/
	double dx;		/**< @brief displacement in x*/
	double dy;		/**< @brief displacement in y*/
	double vX;		/**< @brief velocity in x*/
	double vY;		/**< @brief velocity in y*/
} Bullet;
/** @} end of Bullet */

/**
 * @brief Creates a Bullet object
 * @param asterinix an Asterinix pointer to access bitmaps
 * @return Pointer to an initialized Bullet object
 */
Bullet* createBullet(Bitmap* bitmap, double vX, double vY, int initX, int initY);

/**
 * @brief Draws a bullet
 * @param bullet the bullet to be drawn
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
int drawBullet(Bullet* bullet, char transparency, short trColor);

/**
 * @brief Sets a bullet to move left
 * @param bullet the bullet to update
 */
void bulletMoveLeft(Bullet* bullet);

/**
 * @brief Sets a bullet to move right
 * @param bullet the bullet to update
 */
void bulletMoveRight(Bullet* bullet);

/**
 * @brief Sets a bullet to move up
 * @param bullet the bullet to update
 */
void bulletMoveUp(Bullet* bullet);

/**
 * @brief Sets a bullet to move down
 * @param bullet the bullet to update
 */
void bulletMoveDown(Bullet* bullet);

/**
 * @brief Updates the movement and the life status of a bullet
 * @param Bullet the bullet to update
 */
void updateBullet(Bullet* Bullet, double dt);

/**
 * @brief Clears all movement settings of a bullet
 * @param bullet the bullet to update
 */
void bulletClearAllFlags(Bullet* bullet);

/**@}*/
#endif
