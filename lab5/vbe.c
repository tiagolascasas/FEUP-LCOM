#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"
#include "video_defs.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p)
{
	struct reg86u r;
	mmap_t map;

	if (lm_alloc(sizeof(vbe_mode_info_t), &map) == NULL)
		return 1;

	r.u.w.ax = VBE_FUNCT_1;
	r.u.w.es = PB2BASE(map.phys);	//physical address (phys_bytes)
	r.u.w.di = PB2OFF(map.phys);
	r.u.w.cx = 0x105;
	r.u.b.intno = INT10;

	if( sys_int86(&r) != OK )
	{
		printf("vbe_get_mode_info(): error on sys_int86()\n");
		lm_free(&map);
		return 1;
	}

	*vmi_p = *((vbe_mode_info_t*) map.virtual);	//set to contents of virtual pointer of map

	lm_free(&map);

	return 0;
}

int vbe_get_info(vbe_info_t *conf)
{
	struct reg86u r;
	mmap_t map;

	lm_alloc(sizeof(vbe_info_t), &map);

	r.u.w.ax = VBE_FUNCT_0;
	r.u.w.es = PB2BASE(map.phys);	//physical address (phys_bytes)
	r.u.w.di = PB2OFF(map.phys);
	r.u.b.intno = INT10;

	if( sys_int86(&r) != OK )
	{
		printf("vbe_get_conf(): error on sys_int86()\n");
		return 1;
	}

	*conf = *((vbe_info_t*) map.virtual);	//set to contents of virtual pointer of map
	lm_free(&map);
	return 0;
}

