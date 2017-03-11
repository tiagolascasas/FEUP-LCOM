#ifndef __VIDEODEFS_H
#define __VIDEODEFS_H

/** @defgroup video_defs video_defs
 * @{
 *
 * Constants to configure and work with the graphics card
 */

/*Graphics mode macros*/

#define MODE_RGB_1024X768 0x117	/**< @brief mode 1024x768 16-bit */

#define INT10 0x10			/**< @brief BIOS interrupt call */
#define VBE_FUNCT_0 0x4F00	/**< @brief get VBE controller info */
#define VBE_FUNCT_1 0x4F01	/**< @brief get mode info */
#define VBE_FUNCT_2 0x4F02	/**< @brief set VBE mode */

#define BIT_CORRECTION 4	/**< @brief used to convert bits per pixel to bytes */

/*VBE macros*/

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

/*Colors*/

#define RGB_SPACE_BLUE 0x5	/**< @brief color R=0x0, G=0x0, B=0x5 */
#define RGB_BLACK 0x0		/**< @brief color R=0x0, G=0x0, B=0x0 */

/* Transparency settings */

#define MSB 0x11110000		/**< @brief most significant byte of a short */
#define LSB 0x00001111		/**< @brief less significant byte of a short */
#define NULL_COLOR 0xffff	/**< @brief don't care value for cases in which transparency is not enabled */
#define SHIFT 8				/**< @brief logical shift from LSB to MSB of a short */

/**@}*/
#endif /* __VIDEODEFS_H */
