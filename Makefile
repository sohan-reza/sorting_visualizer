
CC=gcc

all: sorting_viwer.c
	$(CC) sorting_viwer.c -o run 
	
clean:
	rm -f run a.out
