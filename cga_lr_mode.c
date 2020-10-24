#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <i86.h>

#include "cga_lr_mode.h"
#include "cga_board_state.h"

//All Graphics Mode (160x100x16) specific code goes on this file.
u_char __far *cga_lr_get_pixel_byte_address(u_int column, u_int line)
{

	return cga_display_buffer + (line * 160) + ((column >> 1) * 2) + 1;
}

//Graphics mode draw pixel
void cga_lr_draw_pixel(u_int column, u_int line, u_char color)
{
	u_char __far *current_pixel_address = cga_lr_get_pixel_byte_address(column, line);

	u_char current_value = *current_pixel_address;
 	
	u_char low_nibble = current_value & 0x0F;
	u_char high_nibble = current_value & 0xF0;

	if(column & 1)
	{
		low_nibble = color;
	}
	else
	{
		high_nibble = color << 4;
	}

	*current_pixel_address = high_nibble | low_nibble;
}

void cga_lr_quit()
{
}