#include <stdlib.h>
#include "sorting.h"

void count_sort(int array[], int len, int place) {
	int output[len+1];
	
	int mx = (array[0]/place)%10;
	for(int i=1; i<len; i++) {
		if((array[i]/place)%10 > mx) {
			mx=array[i];
		}
	}
	
	int count[mx+1];
	for(int i=0; i<=mx; i++){ count[i]=0; }
	
	for(int i=0; i<len; i++) { count[(array[i]/place) %10]++; }
	
	for(int i=1; i<10; i++){
		count[i]+=count[i-1];
	}
	

	for(int i=len-1; i>=0; i--) {
		
		output[count[(array[i]/place)%10]-1] = array[i];
		count[(array[i]/place)%10]--;
		
	}
	

	
	for(int i=0; i<len; i++){
		array[i]=output[i];
		system("clear");
		list_visualizer(array, len, 1);
	}
	
}

void radix_sort(int arr[], int len) {
	int mx = max(arr, len);
	
	for(int i=1; mx/i>0; i*=10){
		count_sort(arr, len, i);
		
	}
	
}
