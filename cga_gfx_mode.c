#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <i86.h>

#include "cga_gfx_mode.h"
#include "cga_board_state.h"

//All Graphics Mode (320x200x4) specific code goes on this file.

void cga_change_palette(char palette)
{
	palette &= 0x01;
	outp(0x3D9, cga_current_background_color | (palette << 5));
	cga_current_palette = palette;
}

void cga_change_background_color(char color)
{
	color &= 0x0F;
	outp(0x3D9, color | (cga_current_palette << 5));
	cga_current_background_color = color;
}

char __far *cga_gfx_get_pixel_byte_address(uint column, uint line)
{

	return cga_display_buffer + (line*40) + (column >> 2) + (line & 1u) * 0x2000;
}

//Graphics mode draw pixel
void cga_gfx_draw_pixel(uint column, uint line, char color)
{
	char __far *current_pixel_address = cga_gfx_get_pixel_byte_address(column, line);

	char current_value = *current_pixel_address;
	char offset = column & 3;

	current_value = (current_value & ~(0xc0 >> (offset*2))) | ((color << 6) >> (offset * 2));
 	
	*current_pixel_address = current_value;
}

void cga_gfx_draw_byte(uint column_byte, uint line, char byte)
{

	*(cga_display_buffer + ((line>>1)*40) + column_byte + (line & 1u) * 0x2000) = byte;
}