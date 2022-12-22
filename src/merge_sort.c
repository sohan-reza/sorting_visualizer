#include "sorting.h"
#include <stdlib.h>


void merge(int arr[], int l, int r, int s) {
	int n1 = r-l+1;
	int n2 = s-r;

	
	int tmp1[n1], tmp2[n2];
	
	for(int i=0; i<n1; i++) {
		tmp1[i]=arr[l+i];
	}
	
	
	
	for(int i=0; i<n2; i++) {
		
		tmp2[i] = arr[r+i+1];	
	}
	
	//n2--;
	
	
	
	int i=0;
	int j=0;
	int k=l;
	while(i<n1 || j<n2) {
	
		if(i==n1){
			arr[k] = tmp2[j];
			j++;
		}else if(j==n2) {
			arr[k] = tmp1[i];
			i++;
		}else if(tmp1[i]<=tmp2[j]){
			arr[k] = tmp1[i];
			i++;
		}else{
			arr[k] = tmp2[j];
			j++;
		}
		k++;
		
	}
	
	
}

void merge_sort(int arr[], int l, int r, int len) {
	if(l<r) {
		int m = l+(r-l)/2;
		
		merge_sort(arr, l, m, len);
		merge_sort(arr, m+1, r, len);
		
		merge(arr, l, m, r);
		system("clear");
		list_visualizer2(arr, len, 1, m);
	}
}
