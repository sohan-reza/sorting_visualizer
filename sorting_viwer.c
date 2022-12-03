#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_list(int list[], int len){
	for(int i=0; i<len; i++) {
		printf("%2d ", list[i]);
	}
	printf("\n");
}


int max(int list[], int len) {
	int mx = list[0];
	for(int i=1; i<len; i++) {
		if(list[i]>mx){
			mx = list[i];
		}
	}
	return mx;
}

void list_visualizer(int list[], int len) {
	int mx = max(list, len);
	
	int v=mx;
	for(int i=0; i<mx; i++){
		for(int j=0; j<len; j++) {
			
				if(list[j]>=v){
					
					printf(" ▋ "); //■▊▋▍▐▏▎▍   from https://www.i2symbol.com/symbols/geometry
				}else{
					printf("   ");
				}
			
		}
		v--;
			
		printf("\n");
	}
	print_list(list, len);
	system("sleep 0.5");
	
}

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
			list_visualizer(list, len);	
		} 
		if(!flag){break;}
	}
	
	
}


int main(int argc, char **argv){
	int arr[10] = {1,9,5,1,3,5,8,1,60,70};
	//list_visualizer(arr, 10);
	bubble_sort(arr, 10);
	printf("\033[37m\033[41m"); // White foreground / Red background
printf("Something\n");
printf("\033[0m"); 

	return 0;
}

/*
COLOR:

Foreground:

30 Black
31 Red
32 Green
33 Yellow
34 Blue
35 Magenta
36 Cyan
37 White

Background:

40 Black
41 Red
42 Green
43 Yellow
44 Blue
45 Magenta
46 Cyan
47 White

0 Reset all
1 Bold

*/


