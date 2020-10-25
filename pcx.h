#ifndef PCX_H
#define PCX_H

#include "sys/types.h"

#define PCX_READ_SUCCESS 	0
#define PCX_READ_NO_FILE 	1
#define PCX_READ_FAIL		2

typedef struct PCX_IMAGE_
{
	u_int w;
	u_int h;
	u_char __far *content;
} PCX_IMAGE;

u_int pcx_load(const char *filename, PCX_IMAGE* image);
void pcx_unload(PCX_IMAGE image);

typedef struct PCX_FONT_
{
	u_int char_w;
	u_int char_h;

	PCX_IMAGE image;
} PCX_FONT;

u_int pcx_load_font(const char *filename, u_int char_w, u_int char_h, PCX_FONT *font);
void pcx_unload_font(PCX_FONT font);

#endif