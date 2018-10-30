#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <math.h>

#include "video_gr.h"
#include "vbe.h"
#include "i8254.h"
#include "video_defs.h"
#include "sprite.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem;		/* Process address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void *vg_init(unsigned short mode)
{
	struct reg86u r;
	r.u.w.ax = VBE_FUNCT_2;
	r.u.w.bx = BIT(14) | mode;
	r.u.b.intno = INT10;
	if( sys_int86(&r) != OK ) {
		printf("vg_init(): sys_int86() failed \n");
		return;
	}

	vbe_mode_info_t conf;
	vbe_get_mode_info(mode, &conf);

	h_res = conf.XResolution;
	v_res = conf.YResolution;
	bits_per_pixel = conf.BitsPerPixel;

	int response;
	struct mem_range mr;
	unsigned int vram_base = conf.PhysBasePtr;
	printf("Physical address: 0x%x\n", vram_base);
	unsigned int vram_size = (h_res * v_res * bits_per_pixel) / 8;	/*vram size in bytes*/

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if( OK != (response = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("sys_privctl (ADD_MEM) failed: %d\n", response);

	video_mem = vm_map_phys(SELF, (void*)mr.mr_base, vram_size);
	if(video_mem == MAP_FAILED)
		panic("couldn’t map video memory");
}

int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = INT10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}

void vg_set_pixel(unsigned int x, unsigned int y, unsigned long color)
{
	*(video_mem + y * h_res + x) = color;
}

int vg_draw_square(unsigned int x, unsigned int y, unsigned int size, unsigned long color)
{
	if (y >= v_res || x >= h_res || x + size >= h_res || y + size >= v_res || color >= MAX_COLOR)
		return 1;

	unsigned int xi, yi;

	for (yi = y; yi <= y + size; yi++)
	{
		for (xi = x; xi <= x + size; xi++)
			vg_set_pixel(xi, yi, color);
	}
	return 0;
}

int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color)
{
	if (yi >= v_res || xi >= h_res || xf >= h_res || yf >= v_res || color >= MAX_COLOR)
		return 1;

	if (xf - xi == 0)		/*check if m = inf (vertical line), and draw that line*/
	{
		int sum = 1;

		if (yi > yf)
		{
			sum = sum * -1;
		}
		for (; yi != yf; yi += sum)
			vg_set_pixel(xi, yi, color);
		return 0;
	}

	float m = (float)(yf - yi) / (float)(xf - xi);
	int b;

	b = yf - m * xf;

	int sum = 1;

	if (xi > xf)
	{
		sum = sum * -1;
	}

	for (; xi != xf; xi += sum)
	{
		vg_set_pixel(xi, (int)(m * xi + b), color);
	}

	return 0;
}

int vg_draw_xpm(unsigned short x, unsigned short y, char *xpm[])
{
	int wd, ht;
	char* pixmap = (char*)read_xpm(xpm, &wd, &ht);

	if (pixmap == NULL || x + wd >= h_res || y + ht >= v_res)
	{
		return 1;
	}

	int yi, xi, i = 0;
	for (yi = y; yi < y + ht; yi++)
	{
		for (xi = x; xi < x + wd; xi++)
		{
			vg_set_pixel(xi, yi, pixmap[i]);
			i++;
		}
	}
	return 0;

}

Sprite* create_move(char* xpm[], unsigned short x, unsigned short y, unsigned short time, unsigned short hor, short delta)
{
	int xspeed, yspeed;

	if (y >= v_res || x >= h_res)
		return NULL;

	if (hor)
	{
		if (x + delta >= h_res)
			return NULL;
		yspeed = 0;
		xspeed = delta / time;
	}
	else
	{
		if (y + delta >= v_res)
			return NULL;
		xspeed = 0;
		yspeed = delta / time;
	}

	Sprite* sprite = (Sprite*) create_sprite(xpm, x, y, xspeed, yspeed);
	if (sprite != NULL)
	{
		if (x + sprite->width >= h_res || y + sprite->height >= v_res)
			return NULL;
		else return sprite;
	}
	else return NULL;
}

int move_sprite(Sprite* sprite, double dt, unsigned short x, unsigned short y, short delta)
{
	if(delta > 0)	/*if current position is equal or superior to starting position (x) + delta,*/
	{				/*stop moving (just redraw the sprite on the same position)*/
		if (sprite->x - x >= delta || sprite->y - y >= delta)
		{
			if (draw_sprite(sprite) != 0)
				return 1;
			else return 0;
		}
	}
	else	/*same thing as above, but with negative delta*/
	{
		if (x - sprite->x >= abs(delta) || y - sprite->y >= abs(delta))
		{
			if (draw_sprite(sprite) != 0)
				return 1;
			else return 0;
		}
	}

	if (sprite->xspeed != 0)
	{
		int d = sprite->xspeed * dt;
		sprite->x += d;
		if (sprite->x + sprite->width >= h_res || sprite->x <= 0)	/*check if current position is within boundries*/
			return 1;
	}
	if (sprite->yspeed != 0)
	{
		int d = sprite->yspeed * dt;
		sprite->y += d;
		if (sprite->y + sprite->height >= v_res || sprite->y <= 0)	/*check if current position is within boundries*/
			return 1;
	}

	fillBackground();	/*if all checks are good, clears screen and draws the sprite on the new position*/

	if (draw_sprite(sprite) != 0)
		return 1;

	return 0;
}

void fillBackground()
{
	int yi, xi;

	for (yi = 0; yi < v_res; yi++)
	{
		for (xi = 0; xi < h_res; xi++)
			vg_set_pixel(xi, yi, XPM_BLACK);
	}
}
