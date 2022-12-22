#include "sorting.h"
#include <stdlib.h>

void bubble_sort(int list[], int len){
	
	for(int i=0; i<len; i++) {
		int flag=0;
		for(int j=0; j<len-i-1; j++) {
			if(list[j]>list[j+1]) {
				int temp = list[j];
				list[j]=list[j+1];
				list[j+1]=temp;
				flag=1;
			}
			
			system("clear");
			list_visualizer2(list, len, 1, j+1);	
		} 
		if(!flag){break;}
	}
	
	
}
