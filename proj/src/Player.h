#ifndef __PLAYER_H
#define __PLAYER_H

/** @defgroup player player
 * @{
 *
 * Contains the struct player and functions that manipulate it
 */

#include "Sprite.h"
#include "Keyboard.h"
#include "Bullet.h"

#define NUMLIVES 3			/**< @brief number of lives */
#define RESPAWN_TIME 120 	/**< @brief number of timer ticks in 2 seconds */

#define PLAYER_RELOAD_TIME 20	/**< @brief number of ticks until next bullet can be fired */

#define START_DX 4	/**< @brief player starting dx */
#define START_DY 4	/**< @brief player starting dy */

#define MAX_BULLETS 100	/**< @brief max number of bullets */

#include <stdio.h>
#include <math.h>

/** @name Player*/
/**@{
 *
 * @brief Struct with the player sprite, status and movement
 */
typedef struct {
	int alive;		/**< @brief flag that tells if the player is alive or not*/
	int numLives;	/**< @brief number of lives*/
	Sprite* sprite;	/**< @brief player's sprite*/
	int moveLeft;	/**< @brief flag that tells if the player moves left*/
	int moveRight;	/**< @brief flag that tells if the player moves right*/
	int moveUp;		/**< @brief flag that tells if the player moves up*/
	int moveDown;	/**< @brief flag that tells if the player moves down*/
	double dx;		/**< @brief displacement in x*/
	double dy;		/**< @brief displacement in y*/
	Bullet* bullets[MAX_BULLETS + 1];	/**< @brief array of bullets*/
	double timer;	/**< @brief counter for time between shots fired*/
	int justShot;	/**< @brief flag that tells that player has just fired*/
	double lastShot;	/**< @brief time of last shot*/
	double currTime;	/**< @brief current time*/
	char respawnFlag;	/**< @brief flag that tells that respawn protection is enabled*/
	int respawnCounter;	/**< @brief respawn protection counter*/
} Player;
/** @} end of Asteroid */

/**
 * @brief Creates a Player object
 * @param bitmap the player bitmap
 * @return Pointer to an initialized Player object
 */
Player* createPlayer(Bitmap* bitmap);

/**
 * @brief Draws a Player
 * @param player the Player to be drawn
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
int drawPlayer(Player* player, char transparency, short trColor);

/**
 * @brief Updates the movement of a player based on the keys pressed/released
 * @param player the Player to be updated
 * @param key_status the keys status
 */
void playerUpdateMoves(Player* player, key_status_t* key_status);

/**
 * @brief Sets a player to move left
 * @param player the player to update
 */
void playerMoveLeft(Player* player);

/**
 * @brief Sets a player to move right
 * @param player the player to update
 */
void playerMoveRight(Player* player);

/**
 * @brief Sets a player to move up
 * @param player the player to update
 */
void playerMoveUp(Player* player);

/**
 * @brief Sets a player to move down
 * @param player the player to update
 */
void playerMoveDown(Player* player);

/**
 * @brief Updates a player
 * @param player the player to update
 * @param dt the time interval for movement
 * @param key_status the keys status
 */
void updatePlayer(Player* player, double dt, key_status_t* key_status);

/**
 * @brief Clears all movement settings of a Player
 * @param player the Player to update
 */
void playerClearAllFlags(Player* player);

/**
 * @brief Reduces the number of lives of a player by one
 * @param player the Player to be updated
 */
void playerTakeHit(Player* player);

/**
 * @brief Resets a player to its starting position and movement
 * @param player the player to update
 */
void playerReset(Player* player);

/**
 * @brief Resets a player to its starting position, movement and lives
 * @param player the player to update
 */
void playerFullReset(Player* player);

/**
 * @brief Adds a bullet to a player
 * @param player the player to update
 * @param x the mouse's x coordinate
 * @param y the mouse's y coordinate
 * @param bitmap the bullet bitmap
 */
void addBullet(Player* player, double x, double y, Bitmap* bitmap);

/**@}*/
#endif
