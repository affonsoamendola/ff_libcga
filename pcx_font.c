#include "stdlib.h"

#include "pcx.h"

u_int pcx_load_font(const char *filename, u_int char_w, u_int char_h, PCX_FONT *font)
{
	font->char_w = char_w;
	font->char_h = char_h;

	return pcx_load(filename, &(font->image));
}

void pcx_unload_font(PCX_FONT font)
{
	pcx_unload(font.image);
}