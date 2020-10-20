#ifndef FF_LIBCGA_H
#define FF_LIBCGA_H

/*	Information
	
	-------------------
	I/O devices

		3D8h - Mode Control Register (D0)
		3D9h - Color Select Register (D0)
		3DAh - Status Register (D1)
		3DBh - Clear Light Pen Latch
		3DCh - Preset Light Pen Latch
		3D4h - 6845 Index Register *
		3D5h - 6845 Data Register *

		*Apparently theres a dont care information about bits A1 and A2 of these
		2 registers, so possibly there's more addresses that would point here, but 
		probably using those might fuck up with compatibility on other more modern
		cards.

		Unless you have a good reason to use a different address (Cant really think 
		of any), use the ones on the Technical Manual, namely 3D4h and 3D5h

	-------------------
	6845 Registers (3D4h Index, 3D5h Data)
		
		Address  | Register | Register          |         |     | 40x25    | 80x25    | Graphics
		Register | Number   | Type              | Units   | I/O | Alphanum | Alphanum | Modes
		----------------------------------------------------------------------------------------
		0		 | R0		| Hor Total         | Chars   | W   | 38h      | 71h      | 38h
		1		 | R1       | Hor Displayed     | Chars   | W   | 28h      | 50h      | 28h
		2        | R2       | Hor Sync Pos      | Chars   | W   | 2Dh      | 5Ah      | 2Dh
		3        | R3       | Hor Sync Width    | Chars   | W   | 0Ah      | 0Ah      | 0Ah
		4        | R4       | Vert Total        | Char Row| W   | 1Fh      | 1Fh      | 7Fh
		5        | R5       | Vert Total Adjust | Scanline| W   | 06h      | 06h      | 06h
		6        | R6       | Vert Displayed    | Char Row| W   | 19h      | 19h      | 64h
		7        | R7       | Vert Sync Pos     | Char Row| W   | 1Ch      | 1Ch      | 70h
		----------------------------------------------------------------------------------------
		8        | R8       | Interlace Mode    |         | W   | 02h      | 02h      | 02h
		9        | R9       | Max Scanline Addr | Scanline| W   | 07h      | 07h      | 01h
		A		 | R10		| Cursor Start      | Scanline| W   | 06h      | 06h      | 06h
		B		 | R11      | Cursor End        | Scanline| W   | 07h      | 07h      | 07h
		C        | R12      | Start Address (H) |         | W   | 00h      | 00h      | 00h
		D        | R13      | Start Address (L) |         | W   | 00h      | 00h      | 00h
		E        | R14      | Cursor Address (H)|         | RW  |          |          | 
		F        | R15      | Cursor Address (L)|         | RW  |          |          | 
		----------------------------------------------------------------------------------------
		10       | R16      | Light Pen (H)     |         | R   |          |          | 
		11       | R17      | Light Pen (L)     |         | R   |          |          | 

		Taken from IBMs CGA Technical Manual.

	-------------------
	Color-Select register (3D9h)
	
		Alphanumeric Mode
		------------------
			Bit 0 	Selects blue border color
			Bit 1	Selects green border color
			Bit 2	Selects red border color
			Bit 3 	Selects intensified border color
			Bit 4	Selects background colors (?)
			Bit 5	Unused (?)
			Bit 6	Unused
			Bit 7 	Unused

			I believe this means that bit 0 to 3 acts like the IRGB in the attribute byte
			described in Color and Attribute bytes section later
	
		Graphics Mode
		------------------
			Bit 0 	Selects blue background color (When C0 and C1 is 0)
			Bit 1	Selects green background color
			Bit 2	Selects red background color
			Bit 3 	Selects intensified background color
			Bit 4	Selects alternate, intensified set of colors
			Bit 5	Selects active color set
			Bit 6	Unused
			Bit 7 	Unused
			
			Color Sets are Cyan, Magenta and White when bit 5 = 1
			and Green, Red and Brown when bit 5 = 0

		High-res Mode
		------------------
			Bit 0 	Selects blue foreground color
			Bit 1	Selects green foreground color
			Bit 2	Selects red foreground color
			Bit 3 	Selects intensified foreground color
			Bit 4	Unused (?)
			Bit 5	Unused (?)
			Bit 6	Unused
			Bit 7 	Unused
	
	-------------------
	Mode-Control register (3D8h)
		
		Bit 0	1 selects 80x25 alphanum mode
				0 selects 40x25 alphanum mode

		Bit 1	1 selects 320x200 graphics mode
				0 selects alphanum mode

		Bit 2	1 selects B/W mode
				0 selects color mode

		Bit 3	1 enables the video signal, which is disabled when changing modes

		Bit 4	1 selects the high-res (640x200) b/w graphics mode. One of eight colors
				can be selected on direct-drive monitors in this mode by using the
				color-select register.

		Bit 5	1 will change the character background intensity to the blinking attribute
				function for alphanumeric modes. When the high-order attribute is not
				selected, 16 background colors or intensified colors are available.
				Basically if you want blinking on alphanum modes, you need this to be 1,
				and if you need 16 background colors you want this to be 0

		The PC-BIOS supports using a CGA in 7 modes
			
			Code  |
			(hex) | Mode
			--------------------------
			00	  | 40x25 Alphanumeric B/W Mode.
			01	  | 40x25 Alphanumeric Color Mode with 8 background colors and blinking.
			02	  | 80x25 Alphanumeric B/W Mode.
			03	  | 80x25 Alphanumeric Color Mode with 8 background colors and blinking. 
			04	  | 320x200 Graphics Mode 4 Color mode.
			05	  | 320x200 Graphics Mode B/W Mode.
			06	  | 640x200 Graphics Mode B/W Mode. (Unsure what happens if bit 2 is off)

			
	-------------------
	Status register (3DAh)

		Bit 0	1 indicates that a regen-buffer memory access can be made without 
				interfering with the display

		Bit 1	1 indicates that a positive-going edge from the light pen has set
				the light pen's trigger. This trigger is reset when power is turned
				on and may also be cleared by a processor out command to 3DBh.
				No specific data setting is required; the action is address-activated

		Bit 2	The light pen switch is reflected in this bit. The switch is not latched
				or debounced. A 0 indicates that the switch is on

		Bit 3	A 1 indicates that the raster is in a vertical retrace mode.
				Screen-buffer updating can be performed at this time.

	-------------------
	Graphics Modes
		See Mode-Control Register

		CGA has 3 official graphics modes

		Lowres 	160x100 (16 colors)
		Medres	320x200	(4	colors)
		Hires	640x200	(2  colors) 

		---------------------------------
		Low-Res
		
			According to the technical manual, this mode is not supported in ROM, no clue
			what that means.

			160 pixel by 100 rows with each pixel being 2-high by 2-wide (no clue what that means)

			Specifies 1 of 16 colors for each pixel by the I, R, G, B 

			Requires 16000 bytes of read/write memory on the adapter

			Uses memory-mapped graphics

			(Taken from the technical manual)
		
		---------------------------------
		Medium-Res

			320 pixels by 200 rows with each pixel being 1-high by 1-wide

			1 of 4 colors for each pixel

			Formats 4 pixels per byte as follows:

			7   6 |	5   4 |	3   2 | 1   0
			C1 C0 | C1 C0 | C1 C0 | C1 C0
			1st   | 2nd   | 3rd   | 4th
			Pixel | Pixel | Pixel | Pixel

			Color is determined by C1 and C0

			C1 | C0 | Function
			----------------------
			0  | 0  | Color 1 of 16 of the preselected background colors
			----------------------
			0  | 1  | Selects first color of preselected Color Set 1 or Color Set 2
			----------------------
			1  | 0  | Selects second color of preselected Color Set 1 or Color Set 2
			----------------------
			1  | 1  | Selects third color of preselected Color Set 1 or Color Set 2	
			----------------------

			C1 and C0 select 4 of 16 preselected colors. This color selectionm (palette)
			is preloaded in an I/O port

			The two color sets are:

			CS1	 			 | CS2
			-------------------------------
			Color 1 = Green  | 1 = Cyan
			      2 = Red    | 2 = Magenta
			      3 = Brown  | 3 = White
			-------------------------------

			The background colors are the same basic 8 colors define for low-resolution
			graphics, plus 8 alternate intensities defined by the intensity bit, for a
			total of 16 colors, including black and white.

			Requires 16000 bytes of read/write memory on the adapter

			Organizes graphics storage into two banks of 8000 bytes, as follows:

			Address  |	Function
			----------------------
			B8000	 |	Even Scans
			  		 |	8000 Bytes
			  		 |
			----------------------
			B9F3F	 |  Not Used
			         |
			----------------------
			BA000    |  Odd Scans
			         |  8000 Bytes
			         |
			----------------------
			BBF3F	 |  Not Used
					 |
			BBFFF ----------------

			With B8000 being the first pixel at the top left corner of the display

		---------------------------------
		High-Res
			
			640 pixels by 200 rows with each pixel being 1-high by 1-wide

			Supports only black-and-white

			Requires 16000 bytes of read/write memory on the adapter

			Addressing is the same as Med-res, but every bit is a pixel.
				
		---------------------------------
		Color and Attribute bytes
		
		For the Alphanumeric Mode, the characters are defined by two bytes, in the 
		following format:

	         Char Code Byte | Attribute Byte
	        7 6 5 4 3 2 1 0 | 7 6 5 4 3 2 1 0 

	    The attribute byte is defined as following:

	    	7    6 5 4   3 2 1 0
	   	  Blink| R G B | I R G B
		  Fore | Back  |  Fore

		There is a way to disable blink functionality and use 4-bit colors on the
		background as well by disabling bit 5 of the Mode-Control Register.

	-------------------
	Changing Modes

		1. Determine the mode of operation
		2. Reset the video-enable bit in the mode-control register
		3. Program the 6845 CRT Controller to select the mode
		4. Program the mode-control and color-select register including re-enabling the video

	-------------------
	Memory

		The memory used by the CGA adapter is self-contained. It consists of 16k bytes
		of memory without parity. This memory is used both as a display buffer for
		alphanumeric data and as a bit map for graphics data. The regen buffer's address
		starts at B8000h

		There's also a 128k "Reserverd Regen Area" starting at A0000h and ending at C0000h */

#define CGA_MODE_CONTROL_REGISTER 		0x03D8
#define CGA_COLOR_SELECT_REGISTER		0x03D9
#define CGA_STATUS_REGISTER				0x03DA
#define CGA_CLEAR_LIGHT_PEN_LATCH		0x03DB
#define CGA_PRESET_LIGHT_PEN_LATCH		0x03DC

#define CGA_6845_INDEX_REGISTER			0x03D4 //See * above		
#define CGA_6845_DATA_REGISTER			0x03D5 //See * above

//Memory
#define CGA_DEFAULT_DISPLAY_BUFFER		0x000B8000 //Default display buffer

//Most of the following are write-only, see 6845 Registers table above
#define CGA_6845_HOR_TOTAL				0x00
#define CGA_6845_HOR_DISPLAYED			0x01
#define CGA_6845_HOR_SYNC_POSITION		0x02
#define CGA_6845_HOR_SYNC_WIDTH			0x03
#define CGA_6845_VERT_TOTAL				0x04
#define CGA_6845_VERT_TOTAL_ADJUST		0x05
#define CGA_6845_VERT_DISPLAYED			0x06
#define CGA_6845_VERT_SYNC_POSITION		0x07
#define CGA_6845_INTERLACE_MODE			0x08 
#define CGA_6845_MAX_SCANLINE_ADDRESS	0x09
#define CGA_6845_CURSOR_START			0x0A
#define CGA_6845_CURSOR_END				0x0B
#define CGA_6845_START_ADDRESS_HIGH		0x0C 
#define CGA_6845_START_ADDRESS_LOW		0x0D
#define CGA_6845_CURSOR_ADDRESS_HIGH	0x0E //Read/Write
#define CGA_6845_CURSOR_ADDRESS_LOW		0x0F //Read/Write
#define CGA_6845_LIGHT_PEN_HIGH			0x10 //Read/Write
#define CGA_6845_LIGHT_PEN_LOW			0x11 //Read/Write

#define CGA_BLACK 			0x0
#define CGA_BLUE 			0x1
#define CGA_GREEN 			0x2
#define CGA_CYAN	    	0x3
#define CGA_RED	 			0x4
#define CGA_MAGENTA			0x5
#define CGA_BROWN 			0x6
#define CGA_WHITE	    	0x7
#define CGA_GRAY	 		0x8
#define CGA_LIGHT_BLUE		0x9
#define CGA_LIGHT_GREEN 	0xA
#define CGA_LIGHT_CYAN   	0xB
#define CGA_LIGHT_RED		0xC
#define CGA_LIGHT_MAGENTA	0xD
#define CGA_YELLOW   		0xE
#define CGA_WHITE_HIGH		0xF

#define CGA_BLINK			0x80

#define CGA_COLOR(fore, back) 	(back << 4) | fore

//Mode list

#define CGA_MODE_BW40 			0x00
#define CGA_MODE_CO40			0x01
#define CGA_MODE_BW80			0x02
#define CGA_MODE_CO80			0x03
#define CGA_MODE_GRAPHICS		0x04
#define CGA_MODE_GRAPHICS_BW	0x05
#define CGA_MODE_GRAPHICS_HR	0x06

#endif /* END FF_LIBCGA_H */