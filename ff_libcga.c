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

#include "ff_libcga.h"

void change_mode(char mode)
{
	//This uses the BIOS function to change modes

	union REGS in;
	union REGS out;

	in.h.ah = 0x00;
	in.h.al = mode;

	int86(0x10, &in, &out);
}

char __far *display_buffer = (char __far *)0xB8000;

int main(int argc, char const *argv[])
{
	change_mode(CGA_MODE_GRAPHICS);

	*display_buffer = 0xFF;

	return 0;
}

/* 
	Made by Foffonso, started coding on Monday October 19, 2020, during the COVID-19 
	pandemic, I've been stuck home for almost a year now.

	This is starting to get really weird, but things seem to be improving.

	Remember,
	Be Excellent to Each Other!
*/