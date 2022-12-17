
CC := gcc

EXECUTABLE := run
.DEFAULT_GOAL := all

SRC_FILES :=\
			src/bubble_sort.c \
			src/insertion_sort.c \
			src/selection_sort.c \
			src/merge_sort.c \
			src/quick_sort.c \
			src/heap_sort.c \
			src/counting_sort.c \
			sorting_viwer.c 
			

all: sorting_viwer.c
	$(CC) $(SRC_FILES) -o $(EXECUTABLE)
	./$(EXECUTABLE)
	
test: test.c
	$(CC) test.c
	./a.out

clean:
	rm -f $(EXECUTABLE) a.out
