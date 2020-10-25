#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include <dos.h>

#include "pcx.h"

u_int pcx_load(const char *filename, PCX_IMAGE* image_out)
{
	FILE* f = NULL;
	PCX_IMAGE image;

	u_int fail = 0;

	f = fopen(filename, "rb");

	if(f != NULL)
	{
		if(fgetc(f) != 0x0A) return -1;
		fseek(f, 7, SEEK_CUR);

		image.w = fgetc(f);
		image.w |= fgetc(f) << 8;
		image.w += 1; //The file records xlast not width

		image.h = fgetc(f);
		image.h |= fgetc(f) << 8;
		image.h += 1; //The file records ylast not height

		fseek(f, 128, SEEK_SET); //Goto start of image

		u_int segment = 0;

		if(_dos_allocmem((image.w * image.h) / 16, &segment) != 0)
		{
			printf("MEMORY ALLOCATION ERROR.\n");
			exit(-1);
		}

		image.content = (u_char __far *)MK_FP(segment, 0);

		u_char byte;
		u_int run_count;
		u_char run_value;

		u_int line_size = image.w;

		for(u_int l = 0; l < image.h; l++)
		{
			u_int index = 0;

			//Decode a single line
			do
			{
				byte = fgetc(f);

				if((byte & 0xC0) == 0xC0)
				{
					run_count = byte & 0x3F;
					run_value = fgetc(f);
				}
				else
				{
					run_count = 1;
					run_value = byte;
				}

				for(u_int run = 0; run < run_count && index < line_size; run++)
				{
					image.content[index + line_size * l] = run_value;

					index++;
				}

			} while (index < line_size);
		}

		*image_out = image;

		fclose(f);
	}

	return 0;
}

void pcx_unload(PCX_IMAGE image)
{
	if(image.content != NULL)
	{
		_dos_freemem(FP_SEG(image.content));
	}
}