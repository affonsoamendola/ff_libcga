#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h> //For the memset

#include <dos.h>

#include "pcx.h"

#include "cga_lr_image.h"

void cga_lr_optimize_pcx(PCX_IMAGE image_in, CGA_LR_IMAGE* image_out)
{
	u_int segment = 0;

	if(_dos_allocmem((image_in.w * image_in.h) / 16, &segment) != 0)
	{
		printf("MEMORY ALLOCATION ERROR.\n");
		exit(-1);
	}

	image_out->content = (u_char __far *)MK_FP(segment, 0);

	for(int i = 0; i < image_in.w * image_in.h; i++)
	{
		image_out->content[i] = 0xDE;
	}

	u_char current_byte = 0;

	u_int out_index = 1;
	//Loop through all bytes (pixels) on image_in
	for(u_int y = 0; y < image_in.h; y++)
	{
		for(u_int x = 0; x < image_in.w; x++)
		{
			//Shift last color to the first nibble
			current_byte = current_byte << 4;
			current_byte |= image_in.content[x + y * image_in.w];

			//If the column is odd, it means we're on the second pixel, so its time
			//to write to the out image.
			if(x & 1)
			{
				image_out->content[out_index] = current_byte;
				current_byte = 0;

				//Go to next attribute byte on the out image.
				out_index += 2;
			}
		}
	}
}

void cga_lr_load_image(const char* filename, CGA_LR_IMAGE* image_out)
{
	PCX_IMAGE image;

	pcx_load(filename, &image);
	
	cga_lr_optimize_pcx(image, image_out);

	pcx_unload(image);
}

void cga_lr_unload_image(CGA_LR_IMAGE image)
{
	if(image.content != NULL)
	{
		_dos_freemem(FP_SEG(image.content));
	}
}