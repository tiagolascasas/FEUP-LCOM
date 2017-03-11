#include "Game.h"
#include "Utilities.h"
#include "video_defs.h"	/*necessary only to access colors*/
#include "Positions.h"
#include "UART_defs.h"

Game* createGame(Asterinix* asterinix)
{
	Game* game = (Game*) malloc(sizeof(Game));

	game->player = createPlayer(asterinix->bitmaps->ship);

	game->running = RUNNING;

	game->stage = createStage(MENU, asterinix);

	game->connecting = FALSE;
	game->playMultiplayer = FALSE;

	Bitmap* tmp[NUMLIVES + 1];

	tmp[0] = asterinix->bitmaps->lives0;
	tmp[1] = asterinix->bitmaps->lives1;
	tmp[2] = asterinix->bitmaps->lives2;
	tmp[3] = asterinix->bitmaps->lives3;

	game->livesSprite = createMutableSprite(tmp, LIVES_POS_X, LIVES_POS_Y, LIVES_3, NUMLIVES + 1, DEF_VT, DEF_VT);

	game->asterLogo = (Sprite*) createSprite(asterinix->bitmaps->asterLogo, AS_X, AS_Y, DEF_VT, DEF_VT);

	Bitmap* button[BUTTON_BITMAPS];

	button[0] = asterinix->bitmaps->singleplayerButton;
	button[1] = asterinix->bitmaps->singleplayerButtonR;
	game->singleplayerButton = (MutableSprite*) createMutableSprite(button, SPB_X, SPB_Y, 0, 2, DEF_VT, DEF_VT);

	button[0] = asterinix->bitmaps->multiplayerButton;
	button[1] = asterinix->bitmaps->multiplayerButtonR;
	game->multiplayerButton = (MutableSprite*) createMutableSprite(button, MPB_X, MPB_Y, 0, 2, DEF_VT, DEF_VT);

	button[0] = asterinix->bitmaps->highscoresButton;
	button[1] = asterinix->bitmaps->highscoresButtonR;
	game->highscoresButton = (MutableSprite*) createMutableSprite(button, HSB_X, HSB_Y, 0, 2, DEF_VT, DEF_VT);

	button[0] = asterinix->bitmaps->howtoplayButton;
	button[1] = asterinix->bitmaps->howtoplayButtonR;
	game->howtoplayButton = (MutableSprite*) createMutableSprite(button, HTP_X, HTP_Y, 0, 2, DEF_VT, DEF_VT);

	button[0] = asterinix->bitmaps->exitgameButton;
	button[1] = asterinix->bitmaps->exitgameButtonR;
	game->exitgameButton = (MutableSprite*) createMutableSprite(button, EXB_X, EXB_Y, 0, 2, DEF_VT, DEF_VT);

	button[0] = asterinix->bitmaps->backButton;
	button[1] = asterinix->bitmaps->backButtonR;
	game->backButton = (MutableSprite*) createMutableSprite(button, BACKB_X, BACKB_Y, 0, 2, DEF_VT, DEF_VT);

	button[0] = asterinix->bitmaps->resetButton;
	button[1] = asterinix->bitmaps->resetButtonR;
	game->resetButton = (MutableSprite*) createMutableSprite(button, RESETB_X, RESETB_Y, 0, 2, DEF_VT, DEF_VT);

	game->score = (Score*) createScore(asterinix);

	Highscore* hs[MAX_HS];
	readHighscores(hs, asterinix);
	game->hsTable = (HighscoreTable*) createHighscoreTable(hs);

	return game;
}

void play(Game* game, Asterinix* asterinix)
{
	while (game->running)
	{
		updateInput(game, asterinix);	//update input
		if (asterinix->tick)			//if a timer interruption happened
		{
			updateGame(game, asterinix, DEFAULT_DT);	//update game
			draw(game, asterinix);						//draw game
			asterinix->tick = RESET_TICK;				//reset timer interruption flag
			game->stage->time++;						//increase stage time counter
		}
	}
	saveHighscores(game->hsTable, asterinix);	//when it's over, save highscores to file
}

void updateInput(Game* game, Asterinix* asterinix)
{
	int r;
	int ipc_status;
	message msg;
	unsigned char packet;
	unsigned char sc;

	if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
	{
		printf("Error: driver_receive failed with error code %d", r);
	}

	if (is_ipc_notify(ipc_status))
	{
		switch (_ENDPOINT_P(msg.m_source))
		{
		case HARDWARE:
			if (msg.NOTIFY_ARG & asterinix->timer_irqset)
			{
				asterinix->tick = SET_TICK;	//if timer interruption happened, set tick flag
			}
			if (msg.NOTIFY_ARG & asterinix->kbd_irqset)
			{
				sc = kbd_read_asm();		//if a kbd interruption happened, read a single byte
				updateKeyStatus(asterinix->key_status, sc);	//and update key status
			}
			if (msg.NOTIFY_ARG & asterinix->mouse_irqset)
			{
				packet = mouse_read();	//if a mouse interruption happened, read a single byte
				printf("", packet);
				updateMouse(asterinix->mouse, packet);	//and update mouse status
			}
			break;
		default:
			break;
		}
	}
}

void updateGame(Game* game, Asterinix* asterinix, double dt)
{
	if(asterinix->key_status->key_esc || game->stage->exit_game)
	{
		game->running = FALSE;
		return;
	}

	switch(game->stage->stagetype)
	{
		case MENU:
		{
			checkMenuButtons(game, asterinix);

			if (game->stage->finished)
			{
				game->stage->stagetype = game->stage->nextStage;
				game->stage->finished = UNFINISHED;
				game->stage->time = NULL_TIME;
			}
			updateStage(game->stage, dt, asterinix);
		}
		break;

		case SINGLE:
		{
			if (game->stage->time == FIRST_FRAME)
			{
				playerFullReset(game->player);
				game->livesSprite->currentBitmap = LIVES_3;
				int i;
				for (i = 0; i < MAX_ASTEROIDS; i++)
					game->stage->mobs[i] = NULL;
				for (i = 0; i < MAX_BULLETS; i++)
					game->player->bullets[i] = NULL;
			}

			if(asterinix->mouse->leftPressed && game->player->alive)
				addBullet(game->player, asterinix->mouse->x, asterinix->mouse->y, asterinix->bitmaps->shot);

			if(checkCollisions(game->player, game->stage))
				playerReset(game->player);

			if (game->player->alive)
				updatePlayer(game->player, dt, asterinix->key_status);

			int points = checkBulletsCollisions(game->player, game->stage);
			incrementScore(game->score, points, asterinix->font);

			if (game->player->alive)
				updateStage(game->stage, dt, asterinix);

			if (game->player->numLives == LIVES_2)
				updateMutableSprite(game->livesSprite, LIVES_2);
			if (game->player->numLives == LIVES_1)
				updateMutableSprite(game->livesSprite, LIVES_1);
			if (game->player->numLives == LIVES_0)
				updateMutableSprite(game->livesSprite, LIVES_0);

			if (!game->player->alive && !game->stage->addedHighscore)
			{
				game->stage->addedHighscore = TRUE;

				Highscore* score = (Highscore*) createHighscore(asterinix->bitmaps->highscoreTemplate,
																getCurrentTimeStr(), game->score->currentScore);
				if (!addHighscore(game->hsTable, score))
					game->stage->currentGameOver = asterinix->bitmaps->gameOverSP1;
				else game->stage->currentGameOver = asterinix->bitmaps->gameOverSP2;
			}

			if (asterinix->key_status->key_enter && !game->player->alive)
			{
				game->stage->stagetype = MENU;
				game->stage->finished = UNFINISHED;
				game->stage->currentGameOver = NULL;
				game->stage->time = NULL_TIME;
				game->stage->addedHighscore = FALSE;
				resetScore(game->score, asterinix->font);
			}
		}
		break;

		case MULTI:
		{
			if (!game->playMultiplayer)
			{
				char read;
				read = receive_byte_poll();
				if (read == 'a')
				{
					send_byte('b');
					game->playMultiplayer = TRUE;
				}
				if (read == 'b')
				{
					send_byte('b');
					game->playMultiplayer = TRUE;
				}
				if (read == '.')
				{
					if (!game->connecting)
					{
						send_byte('a');
						game->connecting = TRUE;
					}
				}
			}
			else
			{
				//had the comm protocol above worked, multiplayer would be
				//implemented here. Instead, it just returns to main menu
				game->stage->stagetype = MENU;
				game->stage->finished = UNFINISHED;
				game->stage->time = NULL_TIME;
				game->playMultiplayer = FALSE;
				game->connecting = FALSE;
			}

            if (asterinix->mouse->rightPressed)
            {
				game->stage->stagetype = MENU;
				game->stage->finished = UNFINISHED;
				game->stage->time = NULL_TIME;
				game->playMultiplayer = FALSE;
				game->connecting = FALSE;
            }

			break;
		}
		case HIGH:
		{
			if (checkHighscoreButtons(game, asterinix))
			{
				game->stage->stagetype = MENU;
				game->stage->finished = UNFINISHED;
				game->stage->time = NULL_TIME;
			}
			updateStage(game->stage, dt, asterinix);
		}
		case HOW:
		{
			if (asterinix->mouse->rightPressed)
			{
				game->stage->stagetype = MENU;
				game->stage->finished = UNFINISHED;
				game->stage->time = NULL_TIME;
			}
			return;
		}
		break;
	}
}

void draw(Game* game, Asterinix* asterinix)
{
	switch(game->stage->stagetype)
	{
		case MENU:
		{
			drawBitmap(asterinix->bitmaps->background, BG_X, BG_Y, ALIGN_LEFT, FALSE, NULL_COLOR);
			drawSprite(game->asterLogo, TRUE, RGB_SPACE_BLUE);
			drawMutableSprite(game->singleplayerButton, FALSE, NULL_COLOR);
			drawMutableSprite(game->multiplayerButton, FALSE, NULL_COLOR);
			drawMutableSprite(game->highscoresButton, FALSE, NULL_COLOR);
			drawMutableSprite(game->howtoplayButton, FALSE, NULL_COLOR);
			drawMutableSprite(game->exitgameButton, FALSE, NULL_COLOR);
		}
		break;

		case SINGLE:
		{
			if (game->stage->time > NULL_TIME)
			{
				drawBitmap(asterinix->bitmaps->backgroundMatch, BG_X, BG_Y, ALIGN_LEFT, FALSE, NULL_COLOR);
				drawPlayer(game->player, TRUE, RGB_SPACE_BLUE);

				int i;
				for (i = 0; i < MAX_ASTEROIDS; i++)
				{
					if (game->stage->mobs[i] != NULL)
						drawAsteroid(game->stage->mobs[i], TRUE, RGB_SPACE_BLUE);
				}

				drawMutableSprite(game->livesSprite, FALSE, NULL_COLOR);
				drawScore(game->score, FALSE, NULL_COLOR);
				if (game->stage->currentGameOver != NULL)
					drawBitmap(game->stage->currentGameOver, GAME_OVER_X, GAME_OVER_Y, ALIGN_LEFT,
																			FALSE, NULL_COLOR);
				if (game->player->respawnFlag && game->player->alive)
					drawBitmap(asterinix->bitmaps->respawn, RESP_X, RESP_Y, ALIGN_LEFT, TRUE, RGB_SPACE_BLUE);
			}
		}
		break;

		case MULTI:
		{
			drawBitmap(asterinix->bitmaps->background, 0, 0, ALIGN_LEFT, FALSE, NULL_COLOR);
			drawBitmap(asterinix->bitmaps->multiplayerWait, MP_X, MP_Y, ALIGN_LEFT, FALSE, NULL_COLOR);
		}
		break;

		case HIGH:
		{
			drawBitmap(asterinix->bitmaps->background, 0, 0, ALIGN_LEFT, FALSE, NULL_COLOR);
			drawBitmap(asterinix->bitmaps->highscoresLogo, HS_LOGO_X, HS_LOGO_Y, ALIGN_LEFT,
																		TRUE, RGB_SPACE_BLUE);
			drawHighscoreTable(game->hsTable, HSTABLE_X, HSTABLE_Y, asterinix->font,
																			FALSE, NULL_COLOR);
			drawMutableSprite(game->backButton, FALSE, NULL_COLOR);
			drawMutableSprite(game->resetButton, FALSE, NULL_COLOR);
		}
		break;

		case HOW:
		{
			drawBitmap(asterinix->bitmaps->howToPlay, HTP_SCREEN_X, HTP_SCREEN_Y, ALIGN_LEFT,
																			FALSE, NULL_COLOR);
		}
		break;
	}
	drawMouse(asterinix->mouse, TRUE, RGB_SPACE_BLUE);

	copyBuffer(getVBEGraphicsBuffer(), getGraphicsBuffer(), getBufferSize());
	cleanBuffer(getGraphicsBuffer(), getBufferSize(), RGB_BLACK);
}

void checkMenuButtons(Game* game, Asterinix* asterinix)
{
	int mouseX = asterinix->mouse->x;
	int mouseY = asterinix->mouse->y;

	int spWidth1 = game->singleplayerButton->x;
	int spWidth2 = game->singleplayerButton->bitmaps[game->singleplayerButton->currentBitmap]->
											bitmapInfoHeader.width + game->singleplayerButton->x;
	int spHeight1 = game->singleplayerButton->y;
	int spHeight2 = game->singleplayerButton->bitmaps[game->singleplayerButton->currentBitmap]->
											bitmapInfoHeader.height + game->singleplayerButton->y;

	int mpWidth1 = game->multiplayerButton->x;
	int mpWidth2 = game->multiplayerButton->bitmaps[game->multiplayerButton->currentBitmap]->
											bitmapInfoHeader.width + game->multiplayerButton->x;
	int mpHeight1 = game->multiplayerButton->y;
	int mpHeight2 = game->multiplayerButton->bitmaps[game->multiplayerButton->currentBitmap]->
											bitmapInfoHeader.height + game->multiplayerButton->y;

	int hsWidth1 = game->highscoresButton->x;
	int hsWidth2 = game->highscoresButton->bitmaps[game->highscoresButton->currentBitmap]->
										bitmapInfoHeader.width + game->highscoresButton->x;
	int hsHeight1 = game->highscoresButton->y;
	int hsHeight2 = game->highscoresButton->bitmaps[game->highscoresButton->currentBitmap]->
										bitmapInfoHeader.height + game->highscoresButton->y;

	int htpWidth1 = game->howtoplayButton->x;
	int htpWidth2 = game->howtoplayButton->bitmaps[game->howtoplayButton->currentBitmap]->
										bitmapInfoHeader.width + game->howtoplayButton->x;
	int htpHeight1 = game->howtoplayButton->y;
	int htpHeight2 = game->howtoplayButton->bitmaps[game->howtoplayButton->currentBitmap]->
										bitmapInfoHeader.height + game->howtoplayButton->y;

	int exWidth1 = game->exitgameButton->x;
	int exWidth2 = game->exitgameButton->bitmaps[game->exitgameButton->currentBitmap]->
										bitmapInfoHeader.width + game->exitgameButton->x;
	int exHeight1 = game->exitgameButton->y;
	int exHeight2 = game->exitgameButton->bitmaps[game->exitgameButton->currentBitmap]->
										bitmapInfoHeader.height + game->exitgameButton->y;

	/*check if mouse is hovering and/or pressing singleplayer button*/
	if (mouseX > spWidth1 && mouseX < spWidth2 && mouseY > spHeight1 && mouseY < spHeight2)
	{
		updateMutableSprite(game->singleplayerButton, 1);
		if (asterinix->mouse->leftPressed)
		{
			game->stage->finished = FINISHED;
			game->stage->nextStage = SINGLE;
		}
	}
	else updateMutableSprite(game->singleplayerButton, 0);

	/*check if mouse is hovering and/or pressing multiplayer button*/
	if (mouseX > mpWidth1 && mouseX < mpWidth2 && mouseY > mpHeight1 && mouseY < mpHeight2)
	{
		updateMutableSprite(game->multiplayerButton, 1);
		if (asterinix->mouse->leftPressed)
		{
			game->stage->finished = FINISHED;
			game->stage->nextStage = MULTI;
		}
	}
	else updateMutableSprite(game->multiplayerButton, 0);

	/*check if mouse is hovering and/or pressing highscores button*/
	if (mouseX > hsWidth1 && mouseX < hsWidth2 && mouseY > hsHeight1 && mouseY < hsHeight2)
	{
		updateMutableSprite(game->highscoresButton, 1);
		if (asterinix->mouse->leftPressed)
		{
			game->stage->finished = FINISHED;
			game->stage->nextStage = HIGH;
		}
	}
	else updateMutableSprite(game->highscoresButton, 0);

	/*check if mouse is hovering and/or pressing how to play button*/
	if (mouseX > htpWidth1 && mouseX < htpWidth2 && mouseY > htpHeight1 && mouseY < htpHeight2)
	{
		updateMutableSprite(game->howtoplayButton, 1);
		if (asterinix->mouse->leftPressed)
		{
			game->stage->finished = FINISHED;
			game->stage->nextStage = HOW;
		}
	}
	else updateMutableSprite(game->howtoplayButton, 0);

	/*check if mouse is hovering and/or pressing exit button*/
	if (mouseX > exWidth1 && mouseX < exWidth2 && mouseY > exHeight1 && mouseY < exHeight2)
	{
		updateMutableSprite(game->exitgameButton, 1);
		if (asterinix->mouse->leftPressed)
		{
			game->stage->finished = FINISHED;
			game->stage->exit_game = TRUE;
		}
	}
	else updateMutableSprite(game->exitgameButton, 0);
}

int checkHighscoreButtons(Game* game, Asterinix* asterinix)
{
	int mouseX = asterinix->mouse->x;
	int mouseY = asterinix->mouse->y;

	int bWidth1 = game->backButton->x;
	int bWidth2 = game->backButton->bitmaps[game->backButton->currentBitmap]->
								bitmapInfoHeader.width + game->backButton->x;
	int bHeight1 = game->backButton->y;
	int bHeight2 = game->backButton->bitmaps[game->backButton->currentBitmap]->
								bitmapInfoHeader.height + game->backButton->y;

	int rWidth1 = game->resetButton->x;
	int rWidth2 = game->resetButton->bitmaps[game->resetButton->currentBitmap]->
									bitmapInfoHeader.width + game->resetButton->x;
	int rHeight1 = game->resetButton->y;
	int rHeight2 = game->resetButton->bitmaps[game->resetButton->currentBitmap]->
									bitmapInfoHeader.height + game->resetButton->y;

	/*check if mouse is hovering and/or pressing back button*/
	if (mouseX > bWidth1 && mouseX < bWidth2 && mouseY > bHeight1 && mouseY < bHeight2)
	{
		updateMutableSprite(game->backButton, 1);
		if (asterinix->mouse->leftPressed)
			return TRUE;
		else return FALSE;
	}
	else updateMutableSprite(game->backButton, 0);

	/*check if mouse is hovering and/or pressing reset button*/
	if (mouseX > rWidth1 && mouseX < rWidth2 && mouseY > rHeight1 && mouseY < rHeight2)
	{
		updateMutableSprite(game->resetButton, 1);
		if (asterinix->mouse->leftPressed)
			resetHighscores(game->hsTable);
		return FALSE;
	}
	else updateMutableSprite(game->resetButton, 0);

	return FALSE;
}

void send_byte(char byte)
{
	char reg = uart_read(COM1, LSR);
	if (reg & BIT(5))
	{
		printf("Sending byte %c\n", byte);
		uart_send_byte(COM1, byte);
	}
}

char receive_byte_poll()
{
	char reg = uart_read(COM1, LSR);
	char byte = NULL_RESPONSE;
	if (reg & BIT(0))
	{
		byte = uart_read(COM1, RBR);
	}
	printf("Received byte %c\n", byte);
	return byte;
}
