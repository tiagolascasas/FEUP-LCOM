#include "Player.h"

Player* createPlayer(Bitmap* bitmap)
{
	Player* player = (Player*) malloc(sizeof(Player));

	player->alive = ALIVE;
	player->numLives = NUMLIVES;
	player->sprite = createSprite(bitmap, START_X, START_Y, DEFAULT_VX, DEFAULT_VY);
	player->moveLeft = FALSE;
	player->moveRight = FALSE;
	player->moveUp = FALSE;
	player->moveDown = FALSE;
	player->dx = 0;
	player->dy = 0;
	player->justShot = TRUE;
	player->lastShot = 0;
	player->currTime = 0;
	player->respawnFlag = 0;
	player->respawnCounter = 0;

	int i;

	for(i = 0; i < MAX_BULLETS; i++)
	{
		player->bullets[i] = NULL;
	}

	return player;
}

int drawPlayer(Player* player, char transparency, short trColor)
{
	drawSprite(player->sprite, transparency, trColor);

	int i;

	for(i = 0; i < MAX_BULLETS; i++)
	{
		if(player->bullets[i] != NULL)
		{
			drawBullet(player->bullets[i], transparency, trColor);
		}
	}
}

void playerUpdateMoves(Player* player, key_status_t* key_status)
{
	if (key_status->key_w || key_status->key_arrow_up)
		playerMoveUp(player);
	if (key_status->key_s || key_status->key_arrow_down)
		playerMoveDown(player);
	if (key_status->key_a || key_status->key_arrow_left)
		playerMoveLeft(player);
	if (key_status->key_d || key_status->key_arrow_right)
		playerMoveRight(player);
}

void playerMoveLeft(Player* player)
{
	if(!player->moveLeft)
	{
		player->moveLeft = TRUE;
		player->dx -= START_DX;
	}
}

void playerMoveRight(Player* player)
{
	if(!player->moveRight)
		{
			player->moveRight = TRUE;
			player->dx += START_DX;
		}
}

void playerMoveUp(Player* player)
{
	if(!player->moveUp)
		{
			player->moveUp = TRUE;
			player->dy -= START_DX;
		}
}

void playerMoveDown(Player* player)
{
	if(!player->moveDown)
	{
		player->moveDown = TRUE;
		player->dy += START_DY;
	}
}

void playerClearAllFlags(Player* player)
{
	player->moveLeft = FALSE;
	player->moveRight = FALSE;
	player->moveUp = FALSE;
	player->moveDown = FALSE;
	player->dx = 0;
	player->dy = 0;
}

void updatePlayer(Player* player, double dt, key_status_t* key_status)
{
	playerUpdateMoves(player, key_status);

	player->currTime += dt;

	if(player->currTime > player->lastShot + PLAYER_RELOAD_TIME)
	{
		player->justShot = FALSE;
	}

	player->sprite->x += player->dx*dt;

	if (player->sprite->x >= getHorResolution() + player->sprite->bitmap->bitmapInfoHeader.width - 1)
		player->sprite->x = getHorResolution() - player->sprite->bitmap->bitmapInfoHeader.width - 1;
	if (player->sprite->x < 0)
		player->sprite->x = 0;

	player->sprite->y += player->dy*dt;
	if (player->sprite->y >= getVerResolution() + player->sprite->bitmap->bitmapInfoHeader.height - 1)
		player->sprite->y = getVerResolution() - player->sprite->bitmap->bitmapInfoHeader.height - 1;
	if (player->sprite->y < 0)
		player->sprite->y = 0;

	int i;
	for(i = 0; i < MAX_BULLETS; i++)
	{
		if(player->bullets[i] != NULL)
		{
			updateBullet(player->bullets[i], dt);

			if(!player->bullets[i]->alive)
			{
				player->bullets[i] = NULL;
			}
		}
	}

	if (player->respawnFlag)
		player->respawnCounter++;
	if (player->respawnCounter >= RESPAWN_TIME)
	{
		player->respawnCounter = 0;
		player->respawnFlag = FALSE;
	}

	playerClearAllFlags(player);
}

void playerReset(Player* player)
{
	player->sprite->x = START_X;
	player->sprite->y = START_Y;
	player->moveLeft = FALSE;
	player->moveRight = FALSE;
	player->moveUp = FALSE;
	player->moveDown = FALSE;
	player->dx = 0;
	player->dy = 0;
	player->respawnCounter = 0;
}

void playerFullReset(Player* player)
{
	player->alive = ALIVE;
	player->numLives = NUMLIVES;
	player->sprite->x = START_X;
	player->sprite->y = START_Y;
	player->moveLeft = FALSE;
	player->moveRight = FALSE;
	player->moveUp = FALSE;
	player->moveDown = FALSE;
	player->dx = 0;
	player->dy = 0;
	player->respawnCounter = 0;
}

void playerTakeHit(Player* player)
{
	player->numLives--;
	player->respawnFlag = TRUE;

	if(player->numLives == 0)
	{
		player->alive = FALSE;
	}
}

void addBullet(Player* player, double x, double y, Bitmap* bitmap)
{
	if(player->justShot)
	{
		return;
	}

	double halfWidth = player->sprite->bitmap->bitmapInfoHeader.width/4;
	double halfHeight = player->sprite->bitmap->bitmapInfoHeader.height/4;

	double norm = sqrt(pow(x - player->sprite->x + halfWidth, 2) + pow(y - player->sprite->y + halfHeight, 2));

	double vX = (x- player->sprite->x + halfWidth)*BULLET_START_DX/norm;
	double vY = (y- player->sprite->y + halfHeight)*BULLET_START_DY/norm;

	int i;

	for(i = 0; i < MAX_BULLETS; i++)
	{
		if(player->bullets[i] == NULL)
		{
			player->bullets[i] = (Bullet*) createBullet(bitmap, vX, vY, player->sprite->x + halfWidth, player->sprite->y + halfHeight);
			player->lastShot = player->currTime;
			player->justShot = TRUE;
			return;
		}
	}
}
