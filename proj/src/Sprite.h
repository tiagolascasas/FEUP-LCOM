#ifndef __SPRITE_H
#define __SPRITE_H

/** @defgroup sprite sprite
 * @{
 *
 * Contains two sprite structs and functions that manipulate them
 */

#include "Bitmap.h"

/** @name Sprite*/
/**@{
 *
 * @brief Struct for a sprite with a single bitmap
 */
typedef struct {
	Bitmap* bitmap;	/**< @brief bitmap*/
	int x;			/**< @brief x position*/
	int y;			/**< @brief y position*/
	float vx;		/**< @brief velocity in x*/
	float vy;		/**< @brief velocity in y*/
} Sprite;
/** @} end of Sprite */

/**
 * @brief Creates a Sprite object
 * @param bitmap the bitmap of the sprite
 * @param x the x position of the sprite
 * @param y the y position of the sprite
 * @param vx the velocity in x of the sprite
 * @param xy the velocity in y of the sprite
 * @return Pointer to an initialized Sprite object
 */
Sprite* createSprite(Bitmap* bitmap, int x, int y, float vx, float vy);

/**
 * @brief Draws a Sprite at its current position
 * @param sprite the Sprite to be drawn
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
void drawSprite(Sprite* sprite, char transparency, short trColor);

/** @name MutableSprite*/
/**@{
 *
 * @brief Struct for a sprite with multiple bitmaps
 */
typedef struct {
	unsigned int numberOfBitmaps;	/**< @brief number of bitmaps*/
	unsigned int currentBitmap;		/**< @brief index of current bitmap*/
	int x;			/**< @brief x position*/
	int y;			/**< @brief y position*/
	float vx;		/**< @brief velocity in x*/
	float vy;		/**< @brief velocity in y*/
	Bitmap** bitmaps;	/**< @brief array of bitmaps*/
} MutableSprite;
/** @} end of MutableSprite */

/**
 * @brief Creates a MutableSprite object
 * @param bitmaps an array with the bitmaps of the sprite
 * @param x the x position of the sprite
 * @param y the y position of the sprite
 * @param current index of the current bitmap
 * @param n the number of bitmaps
 * @param vx the velocity in x of the sprite
 * @param xy the velocity in y of the sprite
 * @return Pointer to an initialized MutableSprite object
 */
MutableSprite* createMutableSprite(Bitmap** bitmaps, int x, int y, unsigned int current, unsigned int n, float vx, float vy);

/**
 * @brief Draws a MutableSprite at its current position
 * @param sprite the MutableSprite to be drawn
 * @param transparency flag to allow/disallow transparency
 * @param trColor if former argument is allowed, it uses this color as transparency
 */
void drawMutableSprite(MutableSprite* sprite, char transparency, short trColor);

/**
 * @brief Updates the current bitmap of a MutableSprite
 * @param sprite the MutableSprite to be updated
 * @param n index of the new current sprite
 */
void updateMutableSprite(MutableSprite* sprite, int n);

/**@}*/
#endif
