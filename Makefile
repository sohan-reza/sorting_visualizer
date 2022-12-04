
CC=gcc

all: sorting_viwer.c
	$(CC) sorting_viwer.c -o run
	./run
	
test: test.c
	$(CC) test.c
	./a.out

clean:
	rm -f run a.out
