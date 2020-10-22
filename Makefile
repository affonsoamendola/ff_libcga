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
	rm $(bin)
	
run:
	dosbox-x -conf ./dosbox-x-cga.conf ./$(bin)