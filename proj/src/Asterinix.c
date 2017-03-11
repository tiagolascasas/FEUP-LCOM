#include "Asterinix.h"
#include "Utilities.h"

BitmapCollection* createCollection(char* path)
{
	BitmapCollection* bitmaps = (BitmapCollection*) malloc(sizeof(BitmapCollection));

	bitmaps->menu = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/menu.bmp"));
	bitmaps->ship = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/ship.bmp"));
	bitmaps->asteroid = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/asteroid.bmp"));
	bitmaps->shot = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/shot.bmp"));
	bitmaps->lives0 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/lives0.bmp"));
	bitmaps->lives1 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/lives1.bmp"));
	bitmaps->lives2 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/lives2.bmp"));
	bitmaps->lives3 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/lives3.bmp"));
	bitmaps->pointer = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/pointer.bmp"));
	bitmaps->asterLogo = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/asterLogo.bmp"));
	bitmaps->singleplayerButton = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/singleplayerButton.bmp"));
	bitmaps->singleplayerButtonR = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/singleplayerButtonR.bmp"));
	bitmaps->multiplayerButton = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/multiplayerButton.bmp"));
	bitmaps->multiplayerButtonR = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/multiplayerButtonR.bmp"));
	bitmaps->highscoresButton = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/highscoresButton.bmp"));
	bitmaps->highscoresButtonR = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/highscoresButtonR.bmp"));
	bitmaps->howtoplayButton = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/howtoplayButton.bmp"));
	bitmaps->howtoplayButtonR = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/howtoplayButtonR.bmp"));
	bitmaps->exitgameButton = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/exitgameButton.bmp"));
	bitmaps->exitgameButtonR = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/exitgameButtonR.bmp"));
	bitmaps->score = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/score.bmp"));
	bitmaps->highscoresLogo = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/highscoresLogo.bmp"));
	bitmaps->highscoreTemplate = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/highscoreTemplate.bmp"));
	bitmaps->backButton = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/backButton.bmp"));
	bitmaps->backButtonR = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/backButtonR.bmp"));
	bitmaps->resetButton = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/resetButton.bmp"));
	bitmaps->resetButtonR = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/resetButtonR.bmp"));
	bitmaps->gameOverSP1 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/gameOverSP1.bmp"));
	bitmaps->gameOverSP2 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/gameOverSP2.bmp"));
	bitmaps->multiplayerWait = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/multiplayerWait.bmp"));
	bitmaps->howToPlay = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/howToPlay.bmp"));
	bitmaps->background = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/background.bmp"));
	bitmaps->backgroundMatch = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/backgroundMatch.bmp"));
	bitmaps->e1 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e1.bmp"));
	bitmaps->e2 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e2.bmp"));
	bitmaps->e3 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e3.bmp"));
	bitmaps->e4 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e4.bmp"));
	bitmaps->e5 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e5.bmp"));
	bitmaps->e6 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e6.bmp"));
	bitmaps->e7 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e7.bmp"));
	bitmaps->e8 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e8.bmp"));
	bitmaps->e9 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e9.bmp"));
	bitmaps->e10 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e10.bmp"));
	bitmaps->e11 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e11.bmp"));
	bitmaps->e12 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e12.bmp"));
	bitmaps->e13 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e13.bmp"));
	bitmaps->e14 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e14.bmp"));
	bitmaps->e15 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e15.bmp"));
	bitmaps->e16 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e16.bmp"));
	bitmaps->e17 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e17.bmp"));
	bitmaps->e18 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e18.bmp"));
	bitmaps->e19 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e19.bmp"));
	bitmaps->e20 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e20.bmp"));
	bitmaps->e21 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e21.bmp"));
	bitmaps->e22 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e22.bmp"));
	bitmaps->e23 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e23.bmp"));
	bitmaps->e24 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e24.bmp"));
	bitmaps->e25 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e25.bmp"));
	bitmaps->e26 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e26.bmp"));
	bitmaps->e27 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e27.bmp"));
	bitmaps->e28 = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/e28.bmp"));
	bitmaps->respawn = (Bitmap*) loadBitmap(makePath(path, "/bitmaps/respawn.bmp"));

	if (bitmaps->menu == NULL || bitmaps->ship == NULL || bitmaps->asteroid == NULL ||
		bitmaps->shot == NULL || bitmaps->lives1 == NULL || bitmaps->lives1 == NULL ||
		bitmaps->lives2 == NULL || bitmaps->lives3 == NULL || bitmaps->pointer == NULL ||
		bitmaps->asterLogo == NULL || bitmaps->singleplayerButton == NULL ||
		bitmaps->exitgameButton == NULL || bitmaps->score == NULL ||
		bitmaps->highscoresLogo == NULL || bitmaps->highscoreTemplate == NULL ||
		bitmaps->gameOverSP1 == NULL || bitmaps->gameOverSP2 == NULL ||
		bitmaps->multiplayerWait == NULL || bitmaps->howToPlay == NULL ||
		bitmaps->howtoplayButton == NULL || bitmaps->background == NULL ||
		bitmaps->backgroundMatch == NULL || bitmaps->singleplayerButtonR == NULL ||
		bitmaps->multiplayerButtonR == NULL || bitmaps->highscoresButtonR == NULL ||
		bitmaps->howtoplayButtonR == NULL || bitmaps->resetButtonR == NULL ||
		bitmaps->backButtonR == NULL || bitmaps->e1 == NULL ||
		bitmaps->e2 == NULL || bitmaps->e2 == NULL || bitmaps->e2 == NULL ||
		 bitmaps->e2 == NULL || bitmaps->e3 == NULL || bitmaps->e4 == NULL ||
		 bitmaps->e5 == NULL || bitmaps->e6 == NULL || bitmaps->e7 == NULL ||
		 bitmaps->e8 == NULL || bitmaps->e9 == NULL || bitmaps->e10 == NULL ||
		 bitmaps->e11 == NULL || bitmaps->e12 == NULL || bitmaps->e13 == NULL ||
		 bitmaps->e14 == NULL || bitmaps->e15 == NULL || bitmaps->e16 == NULL ||
		 bitmaps->e17 == NULL || bitmaps->e18 == NULL || bitmaps->e19 == NULL ||
		 bitmaps->e20 == NULL || bitmaps->e21 == NULL || bitmaps->e22 == NULL ||
		 bitmaps->e23 == NULL || bitmaps->e24 == NULL || bitmaps->e25 == NULL ||
		 bitmaps->e26 == NULL || bitmaps->e27 == NULL || bitmaps->e28 == NULL ||
		 bitmaps->respawn == NULL)
		printf("Error: failure to retrieve one or more bitmap(s)\n");

	return bitmaps;
}

void deleteCollection(BitmapCollection* bitmaps)
{
	deleteBitmap(bitmaps->menu);
	deleteBitmap(bitmaps->ship);
	deleteBitmap(bitmaps->asteroid);
	deleteBitmap(bitmaps->shot);
	deleteBitmap(bitmaps->lives0);
	deleteBitmap(bitmaps->lives1);
	deleteBitmap(bitmaps->lives2);
	deleteBitmap(bitmaps->lives3);
	deleteBitmap(bitmaps->pointer);
	deleteBitmap(bitmaps->asterLogo);
	deleteBitmap(bitmaps->singleplayerButton);
	deleteBitmap(bitmaps->singleplayerButtonR);
	deleteBitmap(bitmaps->multiplayerButton);
	deleteBitmap(bitmaps->multiplayerButtonR);
	deleteBitmap(bitmaps->highscoresButton);
	deleteBitmap(bitmaps->highscoresButtonR);
	deleteBitmap(bitmaps->howtoplayButton);
	deleteBitmap(bitmaps->howtoplayButtonR);
	deleteBitmap(bitmaps->exitgameButton);
	deleteBitmap(bitmaps->exitgameButtonR);
	deleteBitmap(bitmaps->score);
	deleteBitmap(bitmaps->highscoresLogo);
	deleteBitmap(bitmaps->highscoreTemplate);
	deleteBitmap(bitmaps->backButton);
	deleteBitmap(bitmaps->backButtonR);
	deleteBitmap(bitmaps->resetButton);
	deleteBitmap(bitmaps->resetButtonR);
	deleteBitmap(bitmaps->gameOverSP1);
	deleteBitmap(bitmaps->gameOverSP2);
	deleteBitmap(bitmaps->multiplayerWait);
	deleteBitmap(bitmaps->howToPlay);
	deleteBitmap(bitmaps->background);
	deleteBitmap(bitmaps->backgroundMatch);
	deleteBitmap(bitmaps->e1);
	deleteBitmap(bitmaps->e2);
	deleteBitmap(bitmaps->e3);
	deleteBitmap(bitmaps->e4);
	deleteBitmap(bitmaps->e5);
	deleteBitmap(bitmaps->e6);
	deleteBitmap(bitmaps->e7);
	deleteBitmap(bitmaps->e8);
	deleteBitmap(bitmaps->e9);
	deleteBitmap(bitmaps->e10);
	deleteBitmap(bitmaps->e11);
	deleteBitmap(bitmaps->e12);
	deleteBitmap(bitmaps->e13);
	deleteBitmap(bitmaps->e14);
	deleteBitmap(bitmaps->e15);
	deleteBitmap(bitmaps->e16);
	deleteBitmap(bitmaps->e17);
	deleteBitmap(bitmaps->e18);
	deleteBitmap(bitmaps->e19);
	deleteBitmap(bitmaps->e20);
	deleteBitmap(bitmaps->e21);
	deleteBitmap(bitmaps->e22);
	deleteBitmap(bitmaps->e23);
	deleteBitmap(bitmaps->e24);
	deleteBitmap(bitmaps->e25);
	deleteBitmap(bitmaps->e26);
	deleteBitmap(bitmaps->e27);
	deleteBitmap(bitmaps->e28);
	deleteBitmap(bitmaps->respawn);
	free(bitmaps);
}


Font* createFont(char* path)
{
	Font* font = (Font*) malloc(sizeof(Font));

	font->zero = (Bitmap*) loadBitmap(makePath(path, "/font/0.bmp"));
	font->one = (Bitmap*) loadBitmap(makePath(path, "/font/1.bmp"));
	font->two = (Bitmap*) loadBitmap(makePath(path, "/font/2.bmp"));
	font->three = (Bitmap*) loadBitmap(makePath(path, "/font/3.bmp"));
	font->four = (Bitmap*) loadBitmap(makePath(path, "/font/4.bmp"));
	font->five = (Bitmap*) loadBitmap(makePath(path, "/font/5.bmp"));
	font->six = (Bitmap*) loadBitmap(makePath(path, "/font/6.bmp"));
	font->seven = (Bitmap*) loadBitmap(makePath(path, "/font/7.bmp"));
	font->eight = (Bitmap*) loadBitmap(makePath(path, "/font/8.bmp"));
	font->nine = (Bitmap*) loadBitmap(makePath(path, "/font/9.bmp"));
	font->dots = (Bitmap*) loadBitmap(makePath(path, "/font/_dots.bmp"));
	font->cardinal = (Bitmap*) loadBitmap(makePath(path, "/font/#.bmp"));
	font->lA = (Bitmap*) loadBitmap(makePath(path, "/font/A.bmp"));
	font->lB = (Bitmap*) loadBitmap(makePath(path, "/font/B.bmp"));
	font->lC = (Bitmap*) loadBitmap(makePath(path, "/font/C.bmp"));
	font->lD = (Bitmap*) loadBitmap(makePath(path, "/font/D.bmp"));
	font->lE = (Bitmap*) loadBitmap(makePath(path, "/font/E.bmp"));
	font->lF = (Bitmap*) loadBitmap(makePath(path, "/font/F.bmp"));
	font->lG = (Bitmap*) loadBitmap(makePath(path, "/font/G.bmp"));
	font->lH = (Bitmap*) loadBitmap(makePath(path, "/font/H.bmp"));
	font->lI = (Bitmap*) loadBitmap(makePath(path, "/font/I.bmp"));
	font->lJ = (Bitmap*) loadBitmap(makePath(path, "/font/J.bmp"));
	font->lK = (Bitmap*) loadBitmap(makePath(path, "/font/K.bmp"));
	font->lL = (Bitmap*) loadBitmap(makePath(path, "/font/L.bmp"));
	font->lM = (Bitmap*) loadBitmap(makePath(path, "/font/M.bmp"));
	font->lN = (Bitmap*) loadBitmap(makePath(path, "/font/N.bmp"));
	font->lO = (Bitmap*) loadBitmap(makePath(path, "/font/O.bmp"));
	font->lP = (Bitmap*) loadBitmap(makePath(path, "/font/P.bmp"));
	font->lQ = (Bitmap*) loadBitmap(makePath(path, "/font/Q.bmp"));
	font->lR = (Bitmap*) loadBitmap(makePath(path, "/font/R.bmp"));
	font->lS = (Bitmap*) loadBitmap(makePath(path, "/font/S.bmp"));
	font->lT = (Bitmap*) loadBitmap(makePath(path, "/font/T.bmp"));
	font->lU = (Bitmap*) loadBitmap(makePath(path, "/font/U.bmp"));
	font->lV = (Bitmap*) loadBitmap(makePath(path, "/font/V.bmp"));
	font->lW = (Bitmap*) loadBitmap(makePath(path, "/font/W.bmp"));
	font->lX = (Bitmap*) loadBitmap(makePath(path, "/font/X.bmp"));
	font->lY = (Bitmap*) loadBitmap(makePath(path, "/font/Y.bmp"));
	font->lZ = (Bitmap*) loadBitmap(makePath(path, "/font/Z.bmp"));
	if (font->zero == NULL || font->one == NULL || font->two == NULL ||
		font->three == NULL || font->four == NULL || font->five == NULL ||
		font->six == NULL || font->seven == NULL ||font->eight == NULL ||
		font->nine == NULL || font->dots == NULL || font->cardinal == NULL ||
		font->lA == NULL || font->lB == NULL || font->lC == NULL ||
		font->lD == NULL || font->lE == NULL || font->lF == NULL ||
		font->lG == NULL || font->lH == NULL || font->lI == NULL ||
		font->lJ == NULL || font->lK == NULL || font->lL == NULL ||
		font->lM == NULL || font->lN == NULL || font->lO == NULL ||
		font->lP == NULL || font->lQ == NULL || font->lR == NULL ||
		font->lS == NULL || font->lT == NULL || font->lU == NULL ||
		font->lV == NULL || font->lW == NULL || font->lX == NULL ||
		font->lY == NULL || font->lZ == NULL)
		printf("Error: failure to retreive one or more font characters\n");

	return font;
}

void deleteFont(Font* font)
{
	deleteBitmap(font->zero);
	deleteBitmap(font->one);
	deleteBitmap(font->two);
	deleteBitmap(font->three);
	deleteBitmap(font->four);
	deleteBitmap(font->five);
	deleteBitmap(font->six );
	deleteBitmap(font->seven);
	deleteBitmap(font->eight);
	deleteBitmap(font->nine);
	deleteBitmap(font->dots);
	deleteBitmap(font->cardinal);
	deleteBitmap(font->lA);
	deleteBitmap(font->lB);
	deleteBitmap(font->lC);
	deleteBitmap(font->lD);
	deleteBitmap(font->lE);
	deleteBitmap(font->lF);
	deleteBitmap(font->lG);
	deleteBitmap(font->lH);
	deleteBitmap(font->lI);
	deleteBitmap(font->lJ);
	deleteBitmap(font->lK);
	deleteBitmap(font->lL);
	deleteBitmap(font->lM);
	deleteBitmap(font->lN);
	deleteBitmap(font->lO);
	deleteBitmap(font->lQ);
	deleteBitmap(font->lR);
	deleteBitmap(font->lS);
	deleteBitmap(font->lT);
	deleteBitmap(font->lU);
	deleteBitmap(font->lV);
	deleteBitmap(font->lW);
	deleteBitmap(font->lX);
	deleteBitmap(font->lY);
	deleteBitmap(font->lZ);
	free(font);
}

Asterinix* createAsterinix(char* path)
{
	Asterinix* asterinix = (Asterinix*) malloc(sizeof(Asterinix));

	asterinix->path = path;
	asterinix->timer_irqset = timer_subscribe_int();
	asterinix->kbd_irqset = kbd_subscribe_int();
	asterinix->mouse_irqset = mouse_subscribe_int();
	asterinix->key_status = (key_status_t*) createKeyStatus();
	asterinix->tick = NO_TICK;
	asterinix->bitmaps = (BitmapCollection*) createCollection(path);
	asterinix->font = (Font*) createFont(path);
	asterinix->mouse = (Mouse*) createMouse(asterinix->bitmaps->pointer);

	return asterinix;
}
