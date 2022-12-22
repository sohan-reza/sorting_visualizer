#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

int is_sorted(int arr[], int len) {
	for(int i=1; i<len; i++) {
		if(arr[i]<arr[i-1]){
			return 0;
		}
	}
	return 1;
}

void shuffle(int arr[], int len) {
	for(int i=0; i<len; i++) {
		int pos = (rand()%len);
		int t=arr[i];
		arr[i] = arr[pos];
		arr[pos]=t;
	}
}

void bogo_sort(int arr[], int len) {
	srand(time(NULL));
	while(!is_sorted(arr, len)){
		shuffle(arr, len);
		system("clear");
		list_visualizer(arr, len, 1);
	
	}
}
