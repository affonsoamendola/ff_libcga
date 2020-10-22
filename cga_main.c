/* 	Foffonso's libCGA
	
	A simple library for doing CGA stuff on DOS.
	
	Sources
	- IBM Color/Graphics Monitor Adapter Technical Manual, Personal Computer Hardware Reference Library

	Licensed under GPLv3
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <i86.h>

#include "cga_main.h"

#include "cga_gfx_mode.h"
#include "cga_lr_mode.h"

#include "cga_utils.h"

//Keeps track of current state on the board
uint cga_current_mode = CGA_MODE_CO80;
char cga_current_palette = 1;
char cga_current_background_color = 0;

char __far *cga_display_buffer = (char __far *)CGA_DEFAULT_DISPLAY_BUFFER_EVEN;
//End global state

char __far *cga_get_pixel_byte_address(uint column, uint line)
{
	switch(cga_current_mode)
	{
		case CGA_MODE_GRAPHICS:
			return cga_gfx_get_pixel_byte_address(column, line);
		case CGA_MODE_GRAPHICS_LR:
			return cga_lr_get_pixel_byte_address(column, line);
	}
}

//Returns the bits for the mode-select register
char cga_mode_select_bits(uint mode, uint video_enable, uint blink)
{
	switch(mode)
	{
		case CGA_MODE_CO80:
		case CGA_MODE_GRAPHICS_LR:
			return 0x01 | (video_enable << 3) | (blink << 5);
			break;
	}
}

void cga_set_blink(uint blink_to)
{

	outp(0x03D8, cga_mode_select_bits(cga_current_mode, 1, blink_to));
}

//Changes graphics mode on the PC, using the BIOS
void cga_change_mode(uint mode)
{
	union REGS in;
	union REGS out;

	//This uses the BIOS function to change modes
	switch(mode)
	{
		case CGA_MODE_GRAPHICS:
			in.h.ah = 0x00;
			in.h.al = mode;

			int86(0x10, &in, &out);
			cga_current_mode = mode;
			break;

		case CGA_MODE_GRAPHICS_LR:
		case CGA_MODE_CO80:
			in.h.ah = 0x00;
			in.h.al = 0x03;

			int86(0x10, &in, &out);
			cga_current_mode = mode;

			if(mode == CGA_MODE_GRAPHICS_LR)
			{
				outp(0x03D4, 4);
				outp(0x03D5, 0x7F);
				outp(0x03D4, 6);
				outp(0x03D5, 0x64);
				outp(0x03D4, 7);
				outp(0x03D5, 0x70);
				outp(0x03D4, 9);
				outp(0x03D5, 0x01);
				cga_set_blink(CGA_BLINK_OFF);

				for(int y = 0; y < 100; y++)
				{
					for(int x = 0; x < 80; x++)
					{
						*(cga_display_buffer + (y * 160) + x*2) = 0xDE;
						*(cga_display_buffer + (y * 160) + x*2 + 1) = 0x00;
					}
				}
			}
			break;
	}	
}

//Generic draw pixel function
void cga_draw_pixel(uint column, uint line, char color)
{
	//If mode is graphics (320x200) call its function;
	switch(cga_current_mode)
	{
		case CGA_MODE_GRAPHICS:
			cga_gfx_draw_pixel(column, line, color);
			break;
		case CGA_MODE_GRAPHICS_LR:
			cga_lr_draw_pixel(column, line, color);
			break;
	}
}

int main(int argc, char const *argv[])
{
	cga_change_mode(CGA_MODE_GRAPHICS_LR);

	cga_lr_draw_pixel(0, 0, 0x1);
	cga_lr_draw_pixel(1, 1, 0x2);
	cga_lr_draw_pixel(2, 2, 0x3);
	cga_lr_draw_pixel(3, 3, 0x4);
	cga_lr_draw_pixel(4, 4, 0x5);
	cga_lr_draw_pixel(5, 5, 0x6);
	cga_lr_draw_pixel(6, 6, 0x7);
	cga_lr_draw_pixel(7, 7, 0x8);
	cga_lr_draw_pixel(8, 8, 0x9);
	cga_lr_draw_pixel(9, 9, 0xA);
	cga_lr_draw_pixel(10, 10, 0xB);
	cga_lr_draw_pixel(11, 11, 0xC);
	cga_lr_draw_pixel(12, 12, 0xD);
	cga_lr_draw_pixel(13, 13, 0xE);
	cga_lr_draw_pixel(14, 14, 0xF);

	getch();
	return 0;
}

/* 
	Made by Foffonso, started coding on Monday October 19, 2020, during the COVID-19 
	pandemic, I've been stuck home for almost a year now.

	This is starting to get really weird, but things seem to be improving.

	Remember,
	Be Excellent to Each Other!
*/