#ifndef CGA_GFX_MODE_H
#define CGA_GFX_MODE_H
//All Graphics Mode (320x200x4) specific header code goes on this file.

void cga_change_palette(char palette);

void cga_change_background_color(char color);

char __far *cga_gfx_get_pixel_byte_address(uint column, uint line);

void cga_gfx_draw_pixel(uint column, uint line, char color);
void cga_gfx_draw_byte(uint column_byte, uint line, char byte);

void cga_gfx_quit();

#endif