source = $(wildcard *.c)
bin = libcga.exe

CC = ia16-elf-gcc
LIBRARY = i86
CFLAGS =
INCLUDE = 

$(bin) : $(source) 
	$(CC) -o$(bin) $(source) -l$(LIBRARY)

.PHONY: clean run

clean:
	rm *.o
	rm $(bin)
	
run:
	dosbox ./$(bin)