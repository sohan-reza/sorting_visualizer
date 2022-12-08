#include "sorting.h"
#include <stdlib.h>

void selection_sort(int data[], int len) {
	for(int i=0; i<len; i++) {
		int small=i;
		for(int j=i+1; j<len; j++) {
			if(data[j]<data[small]) {
				small=j;
			}
		}
		if(small != i){
			int temp=data[small];
			data[small]=data[i];
			data[i]=temp;
		}
		system("clear");
		list_visualizer(data, len, 1);	
		
	}
}
