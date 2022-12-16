#ifndef SORTING_H_
#define SORTING_H_



void list_visualizer(int list[], int len, int who);
void viz(int list[], int len, int who, int key, int key2, int cmp1);

//All sorting algorithm declearation will be there
void bubble_sort(int list[], int len);
void insertion_sort(int list[], int len);
void selection_sort(int list[], int len);
void merge_sort(int list[], int l, int r, int len);
void quick_sort(int list[], int l, int h, int len);

#endif
