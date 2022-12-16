#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"

void heapify(int arr[], int len, int i) {
	int left = i*2 + 1;
	int right = i*2 + 2;
	int mx = i;
	
	if(left < len && arr[left]>arr[mx]) {
		mx=left;
	}
	
	
	if(right < len && arr[right]>arr[mx]) {
		mx=right;
	}
	
	if(mx!=i) {
		int t = arr[mx];
		arr[mx] = arr[i];
		arr[i]=t;
		
		heapify(arr, len, mx);
	}
}

void heap_sort(int arr[], int len) {
	int l=len;
	for(int i=(len/2)-1; i>=0; i--) {
		heapify(arr, len, i);
	}
	system("clear");
	list_visualizer(arr, len, 1);
	
	for(int i=l-1; i>=0; i--) {
		//system("clear");
		//list_visualizer(arr, len, 1);
		int t = arr[i];
		arr[i] = arr[0];
		arr[0]=t;
		l--;
		system("clear");
		list_visualizer(arr, len, 1);
		heapify(arr, l, 0);
		
	}
	
}
