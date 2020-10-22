#ifndef CGA_LR_MODE_H
#define CGA_LR_MODE_H
//All Graphics Mode (320x200x4) specific header code goes on this file.

char __far *cga_lr_get_pixel_byte_address(uint column, uint line);

void cga_lr_draw_pixel(uint column, uint line, char color);
void cga_lr_draw_byte(uint column_byte, uint line, char byte);

#endif