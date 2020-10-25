#ifndef CGA_LR_IMAGE_H
#define CGA_LR_IMAGE_H

#include "pcx.h"

typedef struct CGA_LR_IMAGE_
{
	u_int w;
	u_int h;
	u_char __far *content;
} CGA_LR_IMAGE;

void cga_lr_optimize_pcx(PCX_IMAGE image_in, CGA_LR_IMAGE* image_out);

void cga_lr_load_image(const char* filename, CGA_LR_IMAGE* image_out);
void cga_lr_unload_image(CGA_LR_IMAGE image);

#endif