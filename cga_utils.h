#ifndef CGA_UTILS_H
#define CGA_UTILS_H

void print_far_pointer(char __far * pointer);
void hexdump(void *mem, unsigned int len);
void hexdumpf(void __far *mem, unsigned int len);

#endif