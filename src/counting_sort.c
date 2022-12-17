#include <stdlib.h>
#include <stdio.h>
#include "sorting.h"


void counting_sort(int array[], int len) {
	int output[len+1];
	
	int largest = max(array, len);
	
	int count[largest+1];
	for(int i=0; i<=largest; i++){ count[i]=0; }
	
	for(int i=0; i<len; i++) { count[array[i]]++; }
	
	for(int i=1; i<=largest; i++){
		count[i]+=count[i-1];
	}
	

	for(int i=0; i<len; i++) {
		
		output[count[array[i]]-1] = array[i];
		count[array[i]]--;
		
	}
	

	
	for(int i=0; i<len; i++){
		array[i]=output[i];
		
		system("clear");
		list_visualizer(array, len, 1);
		//list_visualizer(output, len, 1,1);
	}
	
	
}
