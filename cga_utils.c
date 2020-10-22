#include <stdio.h>

void print_far_pointer(char __far * pointer)
{
	printf("%p:", ((long unsigned int)pointer)>>16);
	printf("%p\n", pointer);
}
