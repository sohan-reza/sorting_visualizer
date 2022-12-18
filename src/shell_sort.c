#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

void shell_sort(int array[], int n) {
	for(int interval=n/2; interval>0; interval/=2) {
		for(int i=interval; i<n; i++) {
				int temp = array[i];
      			int j;
      			for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
		   			array[j] = array[j - interval];
     			 }
 
     	 	array[j] = temp;
     	 	
     	 	system("clear");
		  	list_visualizer(array, n, 1);
		}
	}
	
	
	
} 
