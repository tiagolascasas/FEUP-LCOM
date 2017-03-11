#include "Sprite.h"
#include <stdio.h>

Sprite* createSprite(Bitmap* bitmap, int x, int y, float vx, float vy)
{
	Sprite* sprite = (Sprite*) malloc(sizeof(Sprite));

	sprite->bitmap = bitmap;
	sprite->x = x;
	sprite->y = y;
	sprite->vx = vx;
	sprite->vy = vy;

	return sprite;
}

void drawSprite(Sprite* sprite, char transparency, short trColor)
{
	drawBitmap(sprite->bitmap, sprite->x, sprite->y, ALIGN_LEFT, transparency, trColor);
}

MutableSprite* createMutableSprite(Bitmap** bitmaps, int x, int y, unsigned int current,
														unsigned int n, float vx, float vy)
{
	MutableSprite* sprite = (MutableSprite*) malloc(sizeof(MutableSprite));

	sprite->x = x;
	sprite->y = y;
	sprite->vx = vx;
	sprite->vy = vy;
	sprite->currentBitmap = current;
	sprite->numberOfBitmaps = n;
	sprite->bitmaps = (Bitmap**) malloc(n * sizeof(Bitmap*));
	int i;
	for (i = 0; i < n; i++)
		sprite->bitmaps[i] = bitmaps[i];
	return sprite;
}

void drawMutableSprite(MutableSprite* sprite, char transparency, short trColor)
{
	drawBitmap(sprite->bitmaps[sprite->currentBitmap], sprite->x, sprite->y,
												ALIGN_LEFT, transparency, trColor);
}

void updateMutableSprite(MutableSprite* sprite, int n)
{
	sprite->currentBitmap = n;
}
