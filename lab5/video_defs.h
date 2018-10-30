#ifndef __VIDEODEFS_H
#define __VIDEODEFS_H

#define MODE_640X480 0x101
#define MODE_800X600 0x103
#define MODE_1024X768 0x105
#define MODE_1280X1024 0x107

#define INT10 0x10
#define VBE_FUNCT_0 0x4F00	//get VBE controller info
#define VBE_FUNCT_1 0x4F01	//get mode info
#define VBE_FUNCT_2 0x4F02	//set VBE mode

#define MAX_COLOR 64
#define XPM_BLACK 0

#define DT 0.016666667		// 1/60

#endif /* __VIDEODEFS_H */
