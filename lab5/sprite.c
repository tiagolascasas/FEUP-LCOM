#include "sprite.h"

Sprite* create_sprite(char* pic[], int x, int y, int xspeed, int yspeed) {
	//allocate space for the "object"
	Sprite* sp = (Sprite*) malloc ( sizeof(Sprite));
	if( sp == NULL )
		return NULL;
	// read the sprite pixmap
	sp->map = (char*) read_xpm(pic, &(sp->width), &(sp->height));
	if( sp->map == NULL ) {
		free(sp);
		return NULL;
	}
	sp->xspeed = xspeed;
	sp->yspeed = yspeed;
	sp->x = x;
	sp->y = y;
	return sp;
}

int draw_sprite(Sprite* sprite)
{
	if (sprite->map == NULL)
	{
		return 1;
	}

	int yi, xi, i = 0;
	for (yi = sprite->y; yi < sprite->y + sprite->height; yi++)
	{
		for (xi = sprite->x; xi < sprite->x + sprite->width; xi++)
		{
			vg_set_pixel(xi, yi, sprite->map[i]);
			i++;
		}
	}
	return 0;
}
