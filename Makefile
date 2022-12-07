
CC := gcc

EXECUTABLE := run
.DEFAULT_GOAL := all

SRC_FILES :=\
			src/bubble_sort.c \
			sorting_viwer.c

all: sorting_viwer.c
	$(CC) $(SRC_FILES) -o $(EXECUTABLE)
	./$(EXECUTABLE)
	
test: test.c
	$(CC) test.c
	./a.out

clean:
	rm -f $(EXECUTABLE) a.out
