#include "pcx.h"

void cga_lr_optimize_font(PCX_FONT font_in, CGA_LR_FONT* font_out)
{
	//Allocates memory
	u_int segment_even = 0;

	if(_dos_allocmem((font_in.image.w * font_in.image.h) / 16, &segment_even) != 0)
	{
		printf("MEMORY ALLOCATION ERROR.\n");
		exit(-1);
	}

	u_int segment_odd = 0;

	if(_dos_allocmem((font_in.image.w * font_in.image.h) / 16, &segment_odd) != 0)
	{
		printf("MEMORY ALLOCATION ERROR.\n");
		exit(-1);
	}

	font_out->content_even = (u_char __far *)MK_FP(segment_even, 0);
	font_out->content_odd = (u_char __far *)MK_FP(segment_odd, 0);

	

}

void cga_lr_load_font(const char* filename, u_int char_x, u_int char_y, CGA_LR_FONT* font_out)
{
	PCX_FONT font;

	pcx_load_font(filename, char_w, char_h, &font);

	cga_lr_optimize_font(font, font_out);

	pcx_unload_font(font);
}

void cga_lr_unload_image(CGA_LR_FONT font)
{
	if(font_out->content_even != NULL)
	{
		_dos_freemem(FP_SEG(font_out->content_even));
	}

	if(font_out->content_odd != NULL)
	{
		_dos_freemem(FP_SEG(font_out->content_odd));
	}
}