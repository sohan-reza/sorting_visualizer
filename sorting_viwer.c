#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep(), 
#include <sys/ioctl.h> //to get terminal height and width
#include <termios.h> //for getch() implement in linux


#define clr system("clear")


//This is alternative to getch() in windows

int getch(void) 
{ 
    struct termios oldattr, newattr; 
    int ch; 
    tcgetattr(STDIN_FILENO, &oldattr); 
    newattr = oldattr; 
    newattr.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); 
    ch = getchar(); 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); 
    return ch; 
} 


typedef struct COR{
	int row;
	int col;
}COR;

COR coordinate(void){
	struct winsize ws;
	ioctl(0, TIOCGWINSZ, &ws);
	COR temp;
	temp.row = ws.ws_row;
	temp.col = ws.ws_col;
	return temp;
}

int length(char *str) {
	int x=0;
	while(str[x++]!='\0');
	return --x;
}

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

/*
float t=0.9;
	char val[10];// = "sleep 1";
	sprintf(val,"sleep %.1f", t);
	system(val);
*/


void intro_page(){
	clr;
	COR c1 = coordinate();
	char *intro1 = " Sorting Visualizer";
	char *intro= " ";
	char *intro2 = "version 0.0.1";
	char *intro3 = "by Sohan Reza";
	char *intro4 = "It's free and open source!";
	
	
	for(int i=0; i<(c1.row-5)/2; i++){printf("\n");}
	
	for(int i=0; i<((c1.col-length(intro1))/2); i++){printf(" ");}
	printf("%s\n\n", intro1);
	
	for(int i=0; i<(c1.col-length(intro2))/2; i++){printf(" ");}
	printf("%s\n", intro2);
	
	for(int i=0; i<(c1.col-length(intro3))/2; i++){printf(" ");}
	printf("%s\n", intro3);
	
	for(int i=0; i<(c1.col-length(intro4))/2; i++){printf(" ");}
	printf("%s\n", intro4);
	
	for(int i=0; i<(c1.row-5)/2; i++){printf("\n");}
	
}

int max_element(char list[][20]){
	int mx=0;
	for(int i=0; i<10; i+=2){
		int j=0;
		for(; list[i][j]!='\0'; j++){
		
		}
		mx = (j>mx)?j:mx;
	}
	return mx;
}

void show_menu(){
	int default_select=0;
	while(1){
	clr;
	COR c1 = coordinate();
	
	for(int i=0; i<((c1.col-19)/2); i++){printf(" ");}
	
	printf(" Sorting Visualizer");
	
	for(int i=0; i<(c1.row-8)/2; i++){printf("\n");}
	
	printf("Use ↑ and ↓ key to select: \n\n");
	char algorithm_list[10][20] = {"Bubble Sort","Selection Sort","Insertion Sort","Merge Sort","Quick Sort","Heap Sort","Counting Sort","Radix Sort","Bucket Sort","Shell Sort"};
    int mx = max_element(algorithm_list);
    
    
    
    int k=0;
    for(int i=0; i<5; i++){
    	int spc=0;
    	
    	spc = length(algorithm_list[k]);
    	//printf("%d\n", default_select);
    	if(default_select==(i)){
    		printf("\033[30m\033[47m");
    			printf("%d. %s",(i+1), algorithm_list[k]);
    		printf("\033[0m"); 
    	}else{
    		printf("%d. %s",(i+1), algorithm_list[k]);
    	}
    	k++;
    	
    
    	spc = mx-spc;
    	for(int j=0; j<spc; j++){
    		printf(" ");
    	}
    	
    	if(default_select==(5+i)){
    		printf("\033[30m\033[47m");
    			printf("\t\t%2d. %s\n",5+(i+1) , algorithm_list[k]);
    		printf("\033[0m"); 
    	}else{
    		printf("\t\t%2d. %s\n",5+(i+1) , algorithm_list[k]);
    	}
    	k++;
    }
    
    
    //printf("%d", c1.row);
    for(int i=0; i<(c1.row-7)/2; i++){printf("\n");}
    
    
    
    printf("\033[30m\033[47m");
			printf("Press ESC twice to exit.");
			for(int i=0; i<c1.col-24; i++){
				printf(" ");
			}
	printf("\033[0m");
    
    
   	
   	printf("\e[?25l"); //This code for hiding cursor in linux terminal  
   	
   	//This code take arrow key input in linux
   	if (getch() == '\033') { // if the first value is esc
   		if(getch()=='\033'){
   			printf("\e[?25h"); // This line for enable cursor
   			break;
   		} // skip the [
		switch(getch()) { // the real value
		    case 'A':
		        // code for arrow up
		        if(default_select==0){
		        	default_select=9;
		        }else{
		        	default_select--;
		        }
		        break;
		    case 'B':
		        // code for arrow down
		       
		        default_select = (default_select+1)%10;
		        break;
		    case 'C':
		        // code for arrow right
		        default_select +=5;
		        break;
		    case 'D':
		        // code for arrow left
		        default_select -=5;
		        break;
		}
	}
	
	
	
   
    }
    
    
   
}

int main(int argc, char **argv){
	
	//intro_page();
	//sleep(1);
	show_menu();

	int arr[10] = {1,9,5,1,3,5,8,1,60,70};
	//list_visualizer(arr, 10);
	//bubble_sort(arr, 10);
	
	
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


