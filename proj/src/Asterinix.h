#ifndef __ASTERINIX_H
#define __ASTERINIX_H

/** @defgroup asterinix asterinix
 * @{
 *
 * Contains the struct asterinix and bitmaps collections
 */

#include "Timer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Bitmap.h"

#define NO_TICK 0	/**< @brief  @brief didn't get a timer interruption */
#define TICK 1		/**< @brief  @brief got a timer interruption */


/** @name Bitmap collection */
/**@{
 *
 * @brief Struct with pointers to all bitmaps
 */
typedef struct {
	Bitmap* menu;	/**< @brief menu.bmp*/
	Bitmap* ship;	/**< @brief ship.bmp*/
	Bitmap* asteroid;	/**< @brief asteroid*/
	Bitmap* lives0;	/**< @brief lives0.bmp*/
	Bitmap* lives1;	/**< @brief lives1.bmp*/
	Bitmap* lives2;	/**< @brief lives2.bmp*/
	Bitmap* lives3;	/**< @brief lives3.bmp*/
	Bitmap* pointer;	/**< @brief pointer.bmp*/
	Bitmap* asterLogo;	/**< @brief asterLogo.bmp*/
	Bitmap* singleplayerButton;	/**< @brief singleplayerButton.bmp*/
	Bitmap* singleplayerButtonR;/**< @brief singleplayerButtonR.bmp*/
	Bitmap* multiplayerButton;	/**< @brief multiplayerButton.bmp*/
	Bitmap* multiplayerButtonR;	/**< @brief multiplayerButtonR.bmp*/
	Bitmap* highscoresButton;	/**< @brief highscoresButton.bmp*/
	Bitmap* highscoresButtonR;	/**< @brief highscoresButtonR.bmp*/
	Bitmap* howtoplayButton;	/**< @brief howtoplayButton.bmp*/
	Bitmap* howtoplayButtonR;	/**< @brief howtoplayButtonR.bmp*/
	Bitmap* exitgameButton;		/**< @brief exitgameButton.bmp*/
	Bitmap* exitgameButtonR;	/**< @brief exitgameButtonR.bmp*/
	Bitmap* shot;	/**< @brief shot.bmp*/
	Bitmap* score;	/**< @brief score.bmp*/
	Bitmap* highscoresLogo;	/**< @brief highscoresLogo.bmp*/
	Bitmap* highscoreTemplate;	/**< @brief highscoreTemplate.bmp*/
	Bitmap* backButton;	/**< @brief backButton.bmp*/
	Bitmap* backButtonR;	/**< @brief backButtonR.bmp*/
	Bitmap* resetButton;	/**< @brief resetButton.bmp*/
	Bitmap* resetButtonR;	/**< @brief resetButtonR.bmp*/
	Bitmap* gameOverSP1;	/**< @brief gameOverSP1.bmp*/
	Bitmap* gameOverSP2;	/**< @brief gameOverSP2.bmp*/
	Bitmap* multiplayerWait;	/**< @brief multiplayerWait.bmp*/
	Bitmap* howToPlay;	/**< @brief howToPlay.bmp*/
	Bitmap* background;	/**< @brief background.bmp*/
	Bitmap* backgroundMatch;	/**< @brief backgroundMatch.bmp*/
	Bitmap* e1;	/**< @brief e1.bmp*/
	Bitmap* e2;	/**< @brief e2.bmp*/
	Bitmap* e3;	/**< @brief e3.bmp*/
	Bitmap* e4;	/**< @brief e4.bmp*/
	Bitmap* e5;	/**< @brief e5.bmp*/
	Bitmap* e6;	/**< @brief e6.bmp*/
	Bitmap* e7;	/**< @brief e7.bmp*/
	Bitmap* e8;	/**< @brief e8.bmp*/
	Bitmap* e9;	/**< @brief e9.bmp*/
	Bitmap* e10;	/**< @brief e10.bmp*/
	Bitmap* e11;	/**< @brief e11.bmp*/
	Bitmap* e12;	/**< @brief e12.bmp*/
	Bitmap* e13;	/**< @brief e13.bmp*/
	Bitmap* e14;	/**< @brief e14.bmp*/
	Bitmap* e15;	/**< @brief e15.bmp*/
	Bitmap* e16;	/**< @brief e16.bmp*/
	Bitmap* e17;	/**< @brief e17.bmp*/
	Bitmap* e18;	/**< @brief e18.bmp*/
	Bitmap* e19;	/**< @brief e19.bmp*/
	Bitmap* e20;	/**< @brief e20.bmp*/
	Bitmap* e21;	/**< @brief e21.bmp*/
	Bitmap* e22;	/**< @brief e22.bmp*/
	Bitmap* e23;	/**< @brief e23.bmp*/
	Bitmap* e24;	/**< @brief e24.bmp*/
	Bitmap* e25;	/**< @brief e25.bmp*/
	Bitmap* e26;	/**< @brief e26.bmp*/
	Bitmap* e27;	/**< @brief e27.bmp*/
	Bitmap* e28;	/**< @brief e28.bmp*/
	Bitmap* respawn;	/**< @brief respawn.bmp*/
} BitmapCollection;
/** @} end of BitmapCollection*/

/**
 * @brief Loads all non-font bitmaps and fills a BitmapCollection struct with their pointers
 * @param path absolute path passed as an argument to main()
 * @return Pointer to an initialized BitmapCollection object
 */
BitmapCollection* createCollection(char* path);

/**
 * @brief Frees up all memory used by bitmaps
 * @param bitmaps a bitmap collection
 */
void deleteCollection(BitmapCollection* bitmaps);


/** @name Font */
/**@{
 *
 * @brief Struct with pointers to all font bitmaps
 */
typedef struct {
	Bitmap* zero;	/**< @brief font 0*/
	Bitmap* one;	/**< @brief font 1*/
	Bitmap* two;	/**< @brief font 2*/
	Bitmap* three;	/**< @brief font 3*/
	Bitmap* four;	/**< @brief font 4*/
	Bitmap* five;	/**< @brief font 5*/
	Bitmap* six;	/**< @brief font 6*/
	Bitmap* seven;	/**< @brief font 7*/
	Bitmap* eight;	/**< @brief font 8*/
	Bitmap* nine;	/**< @brief font 9*/
	Bitmap* dots;	/**< @brief font :*/
	Bitmap* cardinal;	/**< @brief font #*/
	Bitmap* lA;	/**< @brief font A*/
	Bitmap* lB;	/**< @brief font B*/
	Bitmap* lC;	/**< @brief font C*/
	Bitmap* lD;	/**< @brief font D*/
	Bitmap* lE;	/**< @brief font E*/
	Bitmap* lF;	/**< @brief font F*/
	Bitmap* lG;	/**< @brief font G*/
	Bitmap* lH;	/**< @brief fontH*/
	Bitmap* lI;	/**< @brief font I*/
	Bitmap* lJ;	/**< @brief font J*/
	Bitmap* lK;	/**< @brief fontK*/
	Bitmap* lL;	/**< @brief font L*/
	Bitmap* lM;	/**< @brief fontM*/
	Bitmap* lN; /**< @brief font N*/
	Bitmap* lO;	/**< @brief font O*/
	Bitmap* lP;	/**< @brief font P*/
	Bitmap* lQ;	/**< @brief font Q*/
	Bitmap* lR;	/**< @brief font R*/
	Bitmap* lS;	/**< @brief font S*/
	Bitmap* lT;	/**< @brief font T*/
	Bitmap* lU;	/**< @brief font U*/
	Bitmap* lV;	/**< @brief font V*/
	Bitmap* lW;	/**< @brief font W*/
	Bitmap* lX;	/**< @brief font X*/
	Bitmap* lY;	/**< @brief font Y*/
	Bitmap* lZ;	/**< @brief font Z*/
} Font;
/** @} end of Font*/

/**
 * @brief Loads all font bitmaps and fills a BitmapCollection struct with their pointers
 * @param path absolute path passed as an argument to main()
 * @return Pointer to an initialized Font object
 */
Font* createFont(char* path);

/**
 * @brief Frees up all memory used by font bitmaps
 * @param font a font collection
 */
void deleteFont(Font* font);

/** @name Asterinix */
/**@{
 *
 * @brief Struct with state of devices, their irq subscriptions and all bitmaps
 *
 * It contains the irq subscriptions of the timer, the keyboard and the mouse,
 * the instanciation of the mouse object, the struct with the status of the keys,
 * a string with the absolute path to the executable (passed as argument to main)
 * and all bitmaps.
 */
typedef struct{
	char* path;		/**< @brief  @brief absolute path of the executable, passed as argument to main*/
	int timer_irqset;	/**< @brief irq subscription of timer*/
	int kbd_irqset;		/**< @brief irq subscription of keyboard*/
	int mouse_irqset;	/**< @brief irq subscription of mouse*/
	key_status_t* key_status;	/**< @brief key status struct*/
	char tick;				/**< @brief flag that tells if there was a timer interruption*/
	Mouse* mouse;			/**< @brief mouse object*/
	BitmapCollection* bitmaps;	/**< @brief bitmap collection*/
	Font* font;					/**< @brief font collection*/
} Asterinix;
/** @} end of Asterinix */

/**
 * @brief Creates and Asterinix object, subscribing timer, mouse and keyboard interruptions and loading up bitmaps
 * @param path absolute path passed as an argument to main()
 * @return Pointer to an initialized Asterinix object
 */
Asterinix* createAsterinix(char* path);

/**@}*/
#endif
