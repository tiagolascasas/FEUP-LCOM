#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <math.h>

#include "Graphics.h"
#include "VBE.h"
#include "Asterinix.h"
#include "video_defs.h"

char* video_mem;			/* Process address to which VRAM is mapped */
char* video_mem_buffer;		/* Auxiliar video buffer for double-buffering implementation*/
unsigned h_res;				/* Horizontal screen resolution in pixels */
unsigned v_res;				/* Vertical screen resolution in pixels */
unsigned bits_per_pixel; 	/* Number of VRAM bits per pixel */
unsigned bytes_per_pixel;

unsigned getVerResolution()
{
	return v_res;
}

unsigned getHorResolution()
{
	return h_res;
}

unsigned getBitsPerPixel()
{
	return bits_per_pixel;
}

char* getGraphicsBuffer()
{
	return video_mem_buffer;
}

char* getVBEGraphicsBuffer()
{
	return video_mem;
}

unsigned int getBufferSize()
{
	return h_res * v_res * bytes_per_pixel;
}

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
	bytes_per_pixel = conf.BitsPerPixel / BIT_CORRECTION;

	int response;
	struct mem_range mr;
	unsigned int vram_base = conf.PhysBasePtr;
	unsigned int vram_size = getBufferSize();
	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if( OK != (response = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("sys_privctl (ADD_MEM) failed: %d\n", response);
	video_mem = vm_map_phys(SELF, (void*)mr.mr_base, vram_size);
	video_mem_buffer = malloc(h_res * v_res * bytes_per_pixel);
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
	*((short*)video_mem_buffer + y * h_res + x) = color;
}

void fillBackground(short color)
{
	int yi, xi;

	for (yi = 0; yi < v_res; yi++)
	{
		for (xi = 0; xi < h_res; xi++)
			vg_set_pixel(xi, yi, color);
	}
}
