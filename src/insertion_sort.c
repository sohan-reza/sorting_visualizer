#include "sorting.h"
#include <stdlib.h>

void insertion_sort(int data[], int len) {
	for(int i=1; i<len; i++) {
		int x = data[i];
		int j=i-1;
		while(j>=0 && data[j]>x) {
			data[j+1]=data[j];
			data[j]=x;
			j--;
			system("clear");
			list_visualizer(data, len, 1);	
		}
		
	}
}
