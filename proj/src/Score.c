#include "Score.h"

Score* createScore(Asterinix* asterinix)
{
	Score* score = (Score*) malloc(sizeof(Score));

	score->currentScore = NULL_SCORE;
	score->background = (Sprite*) createSprite(asterinix->bitmaps->score, SCORE_X, SCORE_Y,
																	DEFAULT_V, DEFAULT_V);
	score->algarisms[0] = (Sprite*) createSprite(asterinix->font->zero, ALG_0_X, ALG_0_Y,
																	DEFAULT_V, DEFAULT_V);
	score->algarisms[1] = (Sprite*) createSprite(asterinix->font->zero, ALG_1_X, ALG_1_Y,
																	DEFAULT_V, DEFAULT_V);
	score->algarisms[2] = (Sprite*) createSprite(asterinix->font->zero, ALG_2_X, ALG_2_Y,
																	DEFAULT_V, DEFAULT_V);
	score->algarisms[3] = (Sprite*) createSprite(asterinix->font->zero, ALG_3_X, ALG_3_Y,
																	DEFAULT_V, DEFAULT_V);
	score->algarisms[4] = (Sprite*) createSprite(asterinix->font->zero, ALG_4_X, ALG_4_Y,
																	DEFAULT_V, DEFAULT_V);
	return score;
}

void incrementScore(Score* score, unsigned int increment, Font* font)
{
	score->currentScore += increment;
	int sc = score->currentScore;
	int i;
	for (i = 0; i < MAX_ALGARISMS; i++)
	{
		int newAlgarism = sc % BASE;
		switch(newAlgarism)
		{
		case 0: score->algarisms[i]->bitmap = font->zero; break;
		case 1: score->algarisms[i]->bitmap = font->one; break;
		case 2: score->algarisms[i]->bitmap = font->two; break;
		case 3: score->algarisms[i]->bitmap = font->three; break;
		case 4: score->algarisms[i]->bitmap = font->four; break;
		case 5: score->algarisms[i]->bitmap = font->five; break;
		case 6: score->algarisms[i]->bitmap = font->six; break;
		case 7: score->algarisms[i]->bitmap = font->seven; break;
		case 8: score->algarisms[i]->bitmap = font->eight; break;
		case 9: score->algarisms[i]->bitmap = font->nine; break;
		}
		sc /= BASE;
	}
}

void drawScore(Score* score, char transparency, short trColor)
{
	drawBitmap(score->background->bitmap, score->background->x, score->background->y, ALIGN_LEFT,
																		transparency, trColor);
	drawSprite(score->algarisms[0], transparency, trColor);
	drawSprite(score->algarisms[1], transparency, trColor);
	drawSprite(score->algarisms[2], transparency, trColor);
	drawSprite(score->algarisms[3], transparency, trColor);
	drawSprite(score->algarisms[4], transparency, trColor);
}

void resetScore(Score* score, Font* font)
{
	score->currentScore = 0;
	score->algarisms[0]->bitmap = font->zero;
	score->algarisms[1]->bitmap = font->zero;
	score->algarisms[2]->bitmap = font->zero;
	score->algarisms[3]->bitmap = font->zero;
	score->algarisms[4]->bitmap = font->zero;
}
