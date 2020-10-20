/* 	Foffonso's libCGA
	
	A simple library for doing CGA stuff on DOS.
	
	Sources
	- IBM Color/Graphics Monitor Adapter Technical Manual, Personal Computer Hardware Reference Library

	Licensed under GPLv3
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "ff_libcga.h"

void change_mode()
{
	//From the technical manual, info on modes available on the header.

	/* 	Changing Modes

			1. Determine the mode of operation
			2. Reset the video-enable bit in the mode-control register
			3. Program the 6845 CRT Controller to select the mode
			4. Program the mode-control and color-select register including re-enabling the video */

	//1. Determine the mode of operation

	//I am assuming an unknown mode of operation in this function, so it will just
	//get the adapter to a known mode everytime.

	//2. Reset the video-enable bit in the mode-control register

	outp(CGA_MODE_CONTROL_REGISTER, 0);
}

int main(int argc, char const *argv[])
{
	change_mode();

	return 0;
}

/* 
	Made by Foffonso, started coding on Monday October 19, 2020, during the COVID-19 
	pandemic, I've been stuck home for almost a year now.

	This is starting to get really weird, but things seem to be improving.

	Remember,
	Be Excellent to Each Other!
*/