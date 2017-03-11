#include "Asteroid.h"

Asteroid* createAsteroid(Asterinix* asterinix)
{
	Asteroid* asteroid = (Asteroid*) malloc(sizeof(Asteroid));

	asteroid->alive = ALIVE;

	Bitmap* bitmaps[29];
	bitmaps[0] = asterinix->bitmaps->asteroid;
	bitmaps[1] = asterinix->bitmaps->e1;
	bitmaps[2] = asterinix->bitmaps->e2;
	bitmaps[3] = asterinix->bitmaps->e3;
	bitmaps[4] = asterinix->bitmaps->e4;
	bitmaps[5] = asterinix->bitmaps->e5;
	bitmaps[6] = asterinix->bitmaps->e6;
	bitmaps[7] = asterinix->bitmaps->e7;
	bitmaps[8] = asterinix->bitmaps->e8;
	bitmaps[9] = asterinix->bitmaps->e9;
	bitmaps[10] = asterinix->bitmaps->e10;
	bitmaps[11] = asterinix->bitmaps->e11;
	bitmaps[12] = asterinix->bitmaps->e12;
	bitmaps[13] = asterinix->bitmaps->e13;
	bitmaps[14] = asterinix->bitmaps->e14;
	bitmaps[15] = asterinix->bitmaps->e15;
	bitmaps[16] = asterinix->bitmaps->e16;
	bitmaps[17] = asterinix->bitmaps->e17;
	bitmaps[18] = asterinix->bitmaps->e18;
	bitmaps[19] = asterinix->bitmaps->e19;
	bitmaps[20] = asterinix->bitmaps->e20;
	bitmaps[21] = asterinix->bitmaps->e21;
	bitmaps[22] = asterinix->bitmaps->e22;
	bitmaps[23] = asterinix->bitmaps->e23;
	bitmaps[24] = asterinix->bitmaps->e24;
	bitmaps[25] = asterinix->bitmaps->e25;
	bitmaps[26] = asterinix->bitmaps->e26;
	bitmaps[27] = asterinix->bitmaps->e27;
	bitmaps[28] = asterinix->bitmaps->e28;

	asteroid->sprite = (MutableSprite*) createAsteroidSprite(bitmaps);

	asteroidClearAllFlags(asteroid);
	asteroid->moveLeft = FALSE;
	asteroid->moveRight = FALSE;
	asteroid->moveUp = FALSE;
	asteroid->moveDown = FALSE;
	asteroid->dx = ASTEROID_DEFAULT_DX;
	asteroid->dy = ASTEROID_DEFAULT_DY;

	if(asteroid->sprite->x == 0)
	{
		asteroidMoveRight(asteroid);
	}
	else if(asteroid->sprite->x == (getHorResolution() - bitmaps[0]->bitmapInfoHeader.width - 1))
	{
		asteroidMoveLeft(asteroid);
	}

	if(asteroid->sprite->y == (getVerResolution() - bitmaps[0]->bitmapInfoHeader.height - 1))
	{
		asteroidMoveUp(asteroid);
	}

	return asteroid;
}

void asteroidMoveLeft(Asteroid* asteroid)
{
	if(!asteroid->moveLeft)
	{
		asteroid->moveLeft = TRUE;
		asteroid->dx -= ASTEROID_START_DX;
	}
}

void asteroidMoveRight(Asteroid* asteroid)
{
	if(!asteroid->moveRight)
	{
		asteroid->moveRight = TRUE;
		asteroid->dx += ASTEROID_START_DX;
	}
}

void asteroidMoveUp(Asteroid* asteroid)
{
	if(!asteroid->moveUp)
	{
		asteroid->moveUp = TRUE;
		asteroid->dy -= ASTEROID_START_DX;
	}
}

void asteroidMoveDown(Asteroid* asteroid)
{
	if(!asteroid->moveDown)
	{
		asteroid->moveDown = TRUE;
		asteroid->dy += ASTEROID_START_DY;
	}
}

void asteroidClearAllFlags(Asteroid* asteroid)
{
	asteroid->moveLeft = FALSE;
	asteroid->moveRight = FALSE;
	asteroid->moveUp = FALSE;
	asteroid->moveDown = FALSE;
}

void updateAsteroid(Asteroid* asteroid, double dt)
{
	if (asteroid->alive)
	{
		asteroid->sprite->x += asteroid->dx*dt;
		asteroid->sprite->y += asteroid->dy*dt;
	}
	else if (asteroid->sprite->currentBitmap < asteroid->sprite->numberOfBitmaps)
			asteroid->sprite->currentBitmap++;
}

MutableSprite* createAsteroidSprite(Bitmap** bitmaps)
{
	Coord coord = generateRandomCoord(bitmaps[0]->bitmapInfoHeader.height, bitmaps[0]->bitmapInfoHeader.width);
	MutableSprite* sprite = (MutableSprite*) createMutableSprite(bitmaps, coord.x, coord.y, 0,
																ASTEROID_BITMAPS, ASTEROID_VX, ASTEROID_VY);
	return sprite;
}

void drawAsteroid(Asteroid* asteroid, char transparency, short trColor)
{
	drawMutableSprite(asteroid->sprite, transparency, trColor);
}

Coord generateRandomCoord(int asteroid_height, int asteroid_width)
{
	Coord coord;
	int type = rand() % N_OF_BORDERS;
	if (type == 0)	/*left border*/
	{
		coord.x = 0;
		coord.y = rand() % (getVerResolution() - asteroid_height - 1);
		return coord;
	}
	else if (type == 1)	/*lower border*/
	{
		coord.x = rand() % (getHorResolution() - asteroid_width - 1);
		coord.y = getVerResolution() - asteroid_height - 1;
		return coord;
	}
	else	/*right border*/
	{
		coord.x = getHorResolution() - asteroid_width - 1;
		coord.y = rand() % (getVerResolution() - asteroid_height - 1);
		return coord;
	}
}

int asteroidOutOfMap(Asteroid* asteroid)
{
	if(asteroid->sprite->x < 0 || asteroid->sprite->y < 0 || asteroid->sprite->x > getHorResolution()
														|| asteroid->sprite->y > getVerResolution())
		return TRUE;
	else return FALSE;
}
