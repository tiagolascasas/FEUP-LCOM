#ifndef __GRAPHICS_H
#define __GRAPHICS_H

/** @defgroup graphics graphics
 * @{
 *
 * Contains functions that manipulate graphics
 */

#include "i8254.h"
#include "video_defs.h"
#include "lmlib.h"
#include "Asterinix.h"

/**
 * @brief gets the current vertical resolution
 * @return the current vertical resolution in pixels
 */
unsigned getVerResolution();

/**
 * @brief gets the current horizontal resolution
 * @return the current horizontal resolution in pixels
 */
unsigned getHorResolution();

/**
 * @brief gets the current bits per pixel setting
 * @return the current bits per pixel setting
 */
unsigned getBitsPerPixel();

/**
 * @brief gets a pointer to the auxiliar graphics buffer
 * @return a pointer to the auxiliar graphics buffer
 */
char* getGraphicsBuffer();

/**
 * @brief gets a pointer to the graphics buffer
 * @return a pointer to the graphics buffer
 */
char* getVBEGraphicsBuffer();

/**
 * @brief gets the graphics buffer size in bytes
 * @return the current grahpics buffer size inn bytes
 */
unsigned int getBufferSize();

/**
 * @brief initializes video mode
 * @param the video mode to initialize
 */
void *vg_init(unsigned short mode);

/**
 * @brief returns to text mode
 * @return 1 if it failed, 0 otherwise
 */
int vg_exit(void);

/**
 * @brief sets a pixel on the auxiliar video buffer
 * @param x the x coordinate of the pixel
 * @param y the y coordinate of the pixel
 * @param color the color to fill the pixel with
 */
void vg_set_pixel(unsigned int x, unsigned int y, unsigned long color);

/**
 * @brief fills the auxiliar buffer with a specified color
 * @return the color to fill the buffer with
 */
void fillBackground(short color);

/** @name Coord*/
/**@{
 *
 * @brief Struct that holds a x and y coordinate
 */
typedef struct {
	int x; 	/**< @brief x coordinate*/
	int y;	/**< @brief y coordinate*/
} Coord;
/** @} end of Coord */

/**@}*/
#endif /* __GRAPHICS_H */
