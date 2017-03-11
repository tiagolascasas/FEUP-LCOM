#include "Bullet.h"

Bullet* createBullet(Bitmap* bitmap, double vX, double vY, int initX, int initY)
{
	Bullet* bullet = (Bullet*) malloc(sizeof(Bullet));

	bullet->alive = ALIVE;
	bullet->sprite = (Sprite*) createSprite(bitmap, initX, initY, DEFAULT_VX, DEFAULT_VY);
	bullet->moveLeft = FALSE;
	bullet->moveRight = FALSE;
	bullet->moveUp = FALSE;
	bullet->moveDown = FALSE;
	bullet->dx = vX;
	bullet->dy = vY;
	bullet->vX = vX;
	bullet->vY = vY;

	return bullet;
}

int drawBullet(Bullet* bullet, char transparency, short trColor)
{
	drawSprite(bullet->sprite, transparency, trColor);
}

void bulletMoveLeft(Bullet* bullet)
{
	if(!bullet->moveLeft)
	{
		bullet->moveLeft = TRUE;
		bullet->dx -= 1*BULLET_START_DX;
	}
}

void bulletMoveRight(Bullet* bullet)
{
	if(!bullet->moveRight)
	{
		bullet->moveRight = TRUE;
		bullet->dx += BULLET_START_DX;
	}
}

void bulletMoveUp(Bullet* bullet)
{
	if(!bullet->moveUp)
	{
		bullet->moveUp = TRUE;
		bullet->dy -= BULLET_START_DX;
	}
}

void bulletMoveDown(Bullet* bullet)
{
	if(!bullet->moveDown)
	{
		bullet->moveDown = TRUE;
		bullet->dy += BULLET_START_DY;
	}
}

void bulletClearAllFlags(Bullet* bullet)
{
	bullet->moveLeft = FALSE;
	bullet->moveRight = FALSE;
	bullet->moveUp = FALSE;
	bullet->moveDown = FALSE;
}

void updateBullet(Bullet* bullet, double dt)
{
	bullet->sprite->x += bullet->dx*dt;

	if (bullet->sprite->x >= getHorResolution() + bullet->sprite->bitmap->bitmapInfoHeader.width - 1)
		bullet->alive = FALSE;
	if (bullet->sprite->x < 0)
		bullet->alive = FALSE;

	bullet->sprite->y += bullet->dy*dt;

	if (bullet->sprite->y >= getVerResolution() + bullet->sprite->bitmap->bitmapInfoHeader.height - 1)
		bullet->alive = FALSE;
	if (bullet->sprite->y < 0)
		bullet->alive = FALSE;
}
