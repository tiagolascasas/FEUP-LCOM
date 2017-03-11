#include "Highscores.h"
#include "Utilities.h"

Highscore* createHighscore(Bitmap* background, char* timestamp, unsigned int score)
{
	Highscore* highscore = (Highscore*) malloc(sizeof(Highscore));

	highscore->background = background;
	int i;
	for (i = 0; i < ASCTIME_SIZE; i++)
		highscore->timestamp[i] = timestamp[i];
	highscore->score = score;

	return highscore;
}

void drawHighscore(Highscore* highscore, int x, int y, Font* font, int rank, char transparency,
																				short trColor)
{
	drawBitmap(highscore->background, x, y, ALIGN_LEFT, transparency, trColor);

	int charY = y + Y_CORRECTION;
	int charXrank = x + X_START_RANK;
	int charXscore = x + X_START_SCORE;
	int charXtime = x + X_START_TIME;

	drawBitmap(font->cardinal, charXrank, charY, ALIGN_LEFT, transparency, trColor);
	switch(rank)
	{
		case 1: drawBitmap(font->one, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 2: drawBitmap(font->two, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 3: drawBitmap(font->three, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 4: drawBitmap(font->four, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 5: drawBitmap(font->five, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 6: drawBitmap(font->six, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 7: drawBitmap(font->seven, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 8: drawBitmap(font->eight, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
		case 9: drawBitmap(font->nine, charXrank + X_INC, charY, ALIGN_LEFT, transparency, trColor);
				break;
	}

	int sc = highscore->score;
	int i;
	for (i = 0; i < MAX_ALGARISMS; i++)
	{
		int newAlgarism = sc % BASE;
		switch(newAlgarism)
		{
			case 0: drawBitmap(font->zero, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 1: drawBitmap(font->one, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 2: drawBitmap(font->two, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 3: drawBitmap(font->three, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 4: drawBitmap(font->four, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 5: drawBitmap(font->five, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 6: drawBitmap(font->six, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 7: drawBitmap(font->seven, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 8: drawBitmap(font->eight, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
			case 9: drawBitmap(font->nine, charXscore, charY, ALIGN_LEFT, transparency, trColor);
					break;
		}
		charXscore -= X_INC;
		sc /= BASE;
	}

	for (i = 0; i < ASCTIME_SIZE; i++)
	{
		char character = highscore->timestamp[i];
		switch(character)
		{
		case '0': drawBitmap(font->zero, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '1': drawBitmap(font->one, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '2': drawBitmap(font->two, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '3': drawBitmap(font->three, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '4': drawBitmap(font->four, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '5': drawBitmap(font->five, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '6': drawBitmap(font->six, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '7': drawBitmap(font->seven, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '8': drawBitmap(font->eight, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case '9': drawBitmap(font->nine, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case ':': drawBitmap(font->dots, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'a': case 'A': drawBitmap(font->lA, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'b': case 'B': drawBitmap(font->lB, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'c': case 'C': drawBitmap(font->lC, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'd': case 'D': drawBitmap(font->lD, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'e': case 'E': drawBitmap(font->lE, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'f': case 'F': drawBitmap(font->lF, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'g': case 'G': drawBitmap(font->lG, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'h': case 'H': drawBitmap(font->lH, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'i': case 'I': drawBitmap(font->lI, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'j': case 'J': drawBitmap(font->lJ, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'k': case 'K': drawBitmap(font->lK, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'l': case 'L': drawBitmap(font->lL, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'm': case 'M': drawBitmap(font->lM, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'n': case 'N': drawBitmap(font->lN, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'o': case 'O': drawBitmap(font->lO, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'p': case 'P': drawBitmap(font->lP, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'q': case 'Q': drawBitmap(font->lQ, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'r': case 'R': drawBitmap(font->lR, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 's': case 'S': drawBitmap(font->lS, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 't': case 'T': drawBitmap(font->lT, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'u': case 'U': drawBitmap(font->lU, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'v': case 'V': drawBitmap(font->lV, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'w': case 'W': drawBitmap(font->lW, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'x': case 'X': drawBitmap(font->lX, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'y': case 'Y': drawBitmap(font->lY, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		case 'z': case 'Z': drawBitmap(font->lZ, charXtime, charY, ALIGN_LEFT, transparency, trColor);
							break;
		default: break;
		}
		charXtime += X_INC;
	}
}

int compareHighscores(const void* h1, const void* h2)
{
	Highscore* hs1 = *((Highscore**)h1);
	Highscore* hs2 = *((Highscore**)h2);

	if (hs1->score > hs2->score)
		return -1;					//return values specific for qsort()
	else if (hs1->score == hs2->score)
		return 0;
	else return 1;
}


HighscoreTable* createHighscoreTable(Highscore** highscores)
{
	HighscoreTable* hsTable = (HighscoreTable*) malloc(sizeof(HighscoreTable));

	int i;
	for (i = 0; i < MAX_HS; i++)
		hsTable->table[i] = highscores[i];
	return hsTable;
}

void drawHighscoreTable(HighscoreTable* hsTable, int x, int y, Font* font, char transparency,
																			short trColor)
{
	int i;
	for (i = 0; i < MAX_HS; i++)
		drawHighscore(hsTable->table[i], x, y + Y_INC * i, font, i + 1, transparency, trColor);
}

int addHighscore(HighscoreTable* hsTable, Highscore* highscore)
{
	int i;
	int flag = 0;
	for (i = 0; i < MAX_HS; i++)
	{
		if (hsTable->table[i]->score < highscore->score)
		{
			flag = 1;
			hsTable->table[MAX_HS - 1] = highscore;
			break;
		}
	}
	if (!flag)
		return INSUCCESS;
	else
	{
		qsort(hsTable->table, MAX_HS, sizeof(Highscore*), compareHighscores);
		return SUCCESS;
	}
}

void resetHighscores(HighscoreTable* hsTable)
{
	Highscore* blank = (Highscore*) createHighscore(hsTable->table[0]->background,
														DEFAULT_TIME, DEFAULT_SCORE);
	int i;
	for (i = 0; i < MAX_HS; i++)
		hsTable->table[i] = blank;
}

void readHighscores(Highscore** highscores, Asterinix* asterinix)
{
	FILE* file;
	file = fopen(makePath(asterinix->path, SAVE), "r");
	int i;
	if (file)
	{
		char buffer[LOAD_BUFFER_SIZE];
		fgets(buffer, LOAD_BUFFER_SIZE, file);
		int n = atoi(buffer);
		for (i = 0; i < n; i++)
		{
			fgets(buffer, LOAD_BUFFER_SIZE, file);
			int score = atoi(buffer);
			fgets(buffer, LOAD_BUFFER_SIZE, file);
			char timestamp[ASCTIME_SIZE + 1];
			memcpy(timestamp, buffer, ASCTIME_SIZE);
			timestamp[ASCTIME_SIZE] = '\n';
			highscores[i] = (Highscore*) createHighscore(asterinix->bitmaps->highscoreTemplate,
																			timestamp, score);
		}

	}
	else printf("Error reading file\n");
	fclose(file);

	if (i < MAX_HS)
	{
		while (i < MAX_HS)
		{
			highscores[i] = createHighscore(asterinix->bitmaps->highscoreTemplate,
														DEFAULT_TIME, DEFAULT_SCORE);
			i++;
		}
	}
}

void saveHighscores(HighscoreTable* hsTable, Asterinix* asterinix)
{
	FILE* file;
	file = fopen(makePath(asterinix->path, SAVE), "w");
	if (file)
	{
		char buffer[SAVE_BUFFER_SIZE];
		sprintf(buffer, "%d", MAX_HS);
		fputs(buffer, file);
		fputc('\n', file);
		int i;
		for (i = 0; i < MAX_HS; i++)
		{
			memset(buffer, 0, SAVE_BUFFER_SIZE);
			sprintf(buffer, "%d", hsTable->table[i]->score);
			fputs(buffer, file);
			fputc('\n', file);
			char buffer1[ASCTIME_SIZE + 1];
			memcpy(buffer1, hsTable->table[i]->timestamp, ASCTIME_SIZE);
			buffer1[ASCTIME_SIZE] = '\0';
			fputs(buffer1, file);
			fputc('\n', file);
		}
	}
	else
		printf("Error writting to file\n");
	fclose(file);
}
