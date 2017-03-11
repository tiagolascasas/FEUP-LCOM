#include "Stage.h"

Stage* createStage(Stagetype st, Asterinix* asterinix)
{
	Stage* stage = (Stage*) malloc(sizeof(Stage));

	stage->stagetype = st;
	stage->nextStage = MENU;
	stage->finished = UNFINISHED;
	stage->time = 0;
	stage->current_asteroids = 0;
	stage->exit_game = 0;
	stage->currentGameOver = NULL;
	stage->addedHighscore = FALSE;

	int i;
	for (i = 0; i < MAX_ASTEROIDS; i++)
		stage->mobs[i] = NULL;
}

void updateStage(Stage* stage, double dt, Asterinix* asterinix)
{
	switch(stage->stagetype)
	{
		case MENU: break;

		case SINGLE:
		{
			if (stage->time % ASTEROID_SPAWN_TRIGGER == 0)
			{
				int i;
				for (i = 0; i < MAX_ASTEROIDS; i++)
				{
					if (stage->mobs[i] == NULL)
					{
						stage->mobs[i] = (Asteroid*) createAsteroid(asterinix);
						break;
					}
				}
			}

			int i = 0;
			for(i = 0; i < MAX_ASTEROIDS; i++)
			{
				if (stage->mobs[i] != NULL)
					updateAsteroid(stage->mobs[i], dt);
			}

			for(i = 0; i < MAX_ASTEROIDS; i++)
			{
				if (stage->mobs[i] != NULL && asteroidOutOfMap(stage->mobs[i]))
					stage->mobs[i] = NULL;
				if (stage->mobs[i] != NULL && stage->mobs[i]->sprite->currentBitmap ==
												stage->mobs[i]->sprite->numberOfBitmaps)
					stage->mobs[i] = NULL;
			}
		}
		break;

		case MULTI: case HIGH: case HOW: break;
		default: break;
	}

	if (asterinix->key_status->key_esc)
		stage->exit_game = TRUE;
}

int checkCollisions(Player* player, Stage* stage)
{
	int i;
	int res = 0;

	for(i = 0; i < MAX_ASTEROIDS; i++)
	{
		if(stage->mobs[i] != NULL && colliding(player, stage->mobs[i])
									&& !player->respawnFlag)
		{
			playerTakeHit(player);
			res++;
		}
	}

	return res;
}

int colliding(Player* player, Asteroid* asteroid)
{
	int x1 = player->sprite->x;
	int y1 = player->sprite->y;
	int w1 = player->sprite->bitmap->bitmapInfoHeader.width;
	int h1 = player->sprite->bitmap->bitmapInfoHeader.height;
	int x2 = asteroid->sprite->x;
	int y2 = asteroid->sprite->y;
	int w2 = asteroid->sprite->bitmaps[0]->bitmapInfoHeader.width;
	int h2 = asteroid->sprite->bitmaps[0]->bitmapInfoHeader.height;

	if(x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2)
	{
		return TRUE;
	}

	return FALSE;
}

int checkBulletsCollisions(Player* player, Stage* stage)
{
	int i;
	int res = 0;

	for(i = 0; i < MAX_ASTEROIDS; i++)
	{
		if(stage->mobs[i] != NULL)
		{
			int j;
			for (j = 0; j < MAX_BULLETS; j++)
			{
				if (player->bullets[j] != NULL)
				{
					if (bulletColliding(stage->mobs[i], player->bullets[j]) &&
										stage->mobs[i]->alive == ALIVE)
					{
						stage->mobs[i]->alive = FALSE;
						player->bullets[j]->alive = FALSE;
						res++;
					}
				}
			}
		}
	}

	return res;
}

int bulletColliding(Asteroid* asteroid, Bullet* bullet)
{
	int x1 = bullet->sprite->x;
	int y1 = bullet->sprite->y;
	int w1 = bullet->sprite->bitmap->bitmapInfoHeader.width;
	int h1 = bullet->sprite->bitmap->bitmapInfoHeader.height;
	int x2 = asteroid->sprite->x;
	int y2 = asteroid->sprite->y;
	int w2 = asteroid->sprite->bitmaps[0]->bitmapInfoHeader.width;
	int h2 = asteroid->sprite->bitmaps[0]->bitmapInfoHeader.height;

	if(x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2)
	{
		return TRUE;
	}

	return FALSE;
}
