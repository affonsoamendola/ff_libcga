
typedef struct CGA_LR_FONT_
{
	u_int char_w;
	u_int char_h;

	u_char __far *content_even;
	u_char __far *content_odd;

} CGA_LR_FONT;