#include "sorting.h"
#include <stdlib.h>

int partition(int arr[], int l, int h, int len) {
	int i=l-1;
	int pivot = arr[h];
	
	for(int j=l; j<h; j++) {
		
		if(arr[j] < pivot) {
			
			i++;
			
			system("clear");
			viz(arr, len, 2, i, j, h);
			
			int t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
			
			system("clear");
			viz(arr, len, 2, i, j, h);
		}
		system("clear");
		viz(arr, len, 1, l,h, j);
	}
	
	int t = arr[i+1];
	arr[i+1] = arr[h];
	arr[h]=t;
	system("clear");
	viz(arr, len, 1, l, h, i+1);
	
	return i+1;
}

void quick_sort(int arr[], int l, int h, int len) {
	if(l < h) {
		int pi = partition(arr, l, h, len);
		quick_sort(arr, l, pi-1, len);
		quick_sort(arr, pi+1, h, len);
		
	}
}
