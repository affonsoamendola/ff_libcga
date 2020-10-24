#ifndef CGA_LR_MODE_H
#define CGA_LR_MODE_H
//All Graphics Mode (160x100x16) specific header code goes on this file.

u_char __far *cga_lr_get_pixel_byte_address(u_int column, u_int line);

void cga_lr_draw_pixel(u_int column, u_int line, u_char color);
void cga_lr_draw_byte(u_int column_byte, u_int line, u_char byte);

void cga_lr_draw_char(u_int column, u_int line, u_char color, u_char character);

void cga_lr_quit();
#endif