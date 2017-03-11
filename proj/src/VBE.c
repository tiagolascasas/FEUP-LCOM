#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "VBE.h"
#include "video_defs.h"

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
