#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep(), 
#include <sys/ioctl.h> //to get terminal height and width
#include <termios.h> //for getch() implement in linux
#include <time.h>
#include <stdbool.h>


#include "src/sorting.h"


#define clr system("clear")
#define nocur 	printf("\e[?25l");
#define cur printf("\e[?25h"); 

#define SIZE 1024

int data[SIZE];
float _time = 0.5;
char dur[10];

int step_mode = 0;
int sorting_finish = 0;



/************ kbhit *********/
//this is the kbhit() implementation for linux
void enable_raw_mode()
{
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}

void disable_raw_mode()
{
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

/*******kbhit*************/




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

void list_visualizer(int list[], int len, int who) {
	
	int mx = max(list, len);
	sprintf(dur,"sleep %.1f", _time);
	COR c1 = coordinate();
	//len+=3;
	
	if(who && step_mode && !sorting_finish){
		printf("Press any key to go one step.");
	}
	
	int sub=mx+1;
	if(len<=c1.col/3 && mx<100){
		sub++;
	}
	
	
	
	for(int i=0; i<(c1.row-sub); i++){printf("\n");}
	
	int bar_total_width = 0;
	
	if(len<=c1.col/3){
		bar_total_width = len*3;
	}else{
		bar_total_width=len;
	} 

	int v=mx;
	for(int i=0; i<mx; i++){
	
		for(int i=0; i<(c1.col-bar_total_width)/2; i++){printf(" ");}
	
		for(int j=0; j<len; j++) {
				
				if(list[j]>=v){
					
					if(len<=c1.col/3){
					printf(" ▋ "); //■▊▋▍▐▏▎▍   from https://www.i2symbol.com/symbols/geometry
					}else{
					printf("▋");
					}
					
				}else{
				
					if(len<=c1.col/3){
					printf("   ");
					}else{
					printf(" ");
					}
				}
			
		}
		v--;
		
		printf("\n");
	}
	
	
	if(len<=c1.col/3 && mx<100){
		for(int i=0; i<(c1.col-bar_total_width)/2; i++){printf(" ");}
		print_list(list, len);
	}
	if(time!=0){
		system(dur);
	}
	
	
	//
	if(who && step_mode){
		if(getch()=='\033'){
			getch();
			getch();
		}	
		tcflush(0, TCIFLUSH);
	}
	
	if(who && step_mode==0){
		enable_raw_mode();
		int tt=0;
		if(kbhit()){
			
			printf("Press any key to resume.");
			if(getch()=='\033'){
				getch();
				getch();
			}
			if(getch()=='\033'){
				getch();
				getch();
			}
			
			
		}
		disable_raw_mode();
			tcflush(0, TCIFLUSH);
			
		
	}
	
}



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

void random_data(int size, int height){
	srand(time(NULL));
	
	for(int i=0; i<size; i++) {
		data[i] = (rand()%height-3)+1;
		if(data[i]<0 || data[i]==0){
			data[i]=1;
		}
	}
}


void step_mode_setup(char name[]) {
		int default_select=step_mode;
		
		while(1){
		clr;
		COR c1 = coordinate();
		for(int i=0; i<((c1.col-length(name))/2); i++){printf(" ");}
		
		printf("\033[37m\033[41m");
		printf("%s", name);
		printf("\033[0m");
		for(int i=0; i<((c1.row-5)/2); i++){printf("\n");}
		
		/*center*/
		for(int i=0; i<((c1.col-26)/2); i++){printf(" ");}
		
		
		printf("Use ↑ and ↓ key to select:\n\n");
		char algorithm_list[2][22] = {"Disable.", "Enable."};
	  
	  	
	  
	  //	printf("%d %d\n", length("Use ↑ and ↓ key to select:"), length(algorithm_list[0])+5);
	  
		int k=0;
		for(int i=0; i<2; i++){
			for(int i=0; i<((c1.col-10)/2); i++){printf(" ");}
			if(default_select==(i)){
				printf("\033[30m\033[47m");
					printf("%d. %s\n",(i+1), algorithm_list[i]);
				printf("\033[0m"); 
			}else{
				printf("%d. %s\n",(i+1), algorithm_list[i]);
			}
			
		}
		
		for(int i=0; i<(c1.row-4)/2; i++){printf("\n");}
		
		
		printf("\033[30m\033[47m");
				printf("Press ESC twice to exit.");
				for(int i=0; i<c1.col-24; i++){
					printf(" ");
				}
		printf("\033[0m");
		
	   	
	   	 //This code for hiding cursor in linux terminal  
	   	nocur;
	   	
	   	int d = getch();
	   	if(d==10){
	   			cur;
	   			
	   			clr;
	   			COR c1 = coordinate();
				for(int i=0; i<((c1.col-length(name))/2); i++){printf(" ");}
				
				printf("\033[37m\033[41m");
				printf("%s\n\n", name);
				printf("\033[0m\n");
	   			if(default_select==0){
	   				step_mode=0;
					
					break;
	   				//
	   			}else if(default_select==1){
		   			step_mode=1;
					
					break;
	   			}
	   	}
	   	
	  
	   	
	   	//This code take arrow key input in linux
	   	if (d == '\033') { // if the first value is esc
	   		if(getch()=='\033'){
	   			printf("\e[?25h"); // This line for enable cursor
	   			break;
	   		} // skip the [
			switch(getch()) { // the real value
				case 'A':
				    // code for arrow up
				    if(default_select==0){
				    	default_select=1;
				    }else{
				    	default_select--;
				    }
				    break;
				case 'B':
				    // code for arrow down
				   
				    default_select = (default_select+1)%2;
				    break;
			}
			
			
			
		}
}
}

void set_color(char name[]){
	int default_select=0;
	
	while(1){
	
	int size=0;
	clr;
	COR c1 = coordinate();
	for(int i=0; i<((c1.col-length(name))/2); i++){printf(" ");}
	
	printf("\033[37m\033[41m");
	printf("%s", name);
	printf("\033[0m");
	
	for(int i=0; i<((c1.row-8)/2); i++){printf("\n");}
	
	for(int i=0; i<((c1.col-26)/2); i++){printf(" ");}
	
	printf("Use ↑ and ↓ key to select:\n\n");
	/*
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
  	char algorithm_list[7][10] = {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"};
  
    int k=0;
    for(int i=0; i<7; i++){
    for(int i=0; i<((c1.col-19)/2); i++){printf(" ");}
    	if(default_select==(i)){
    		printf("\033[30m\033[47m");
    			printf("%d. %s\n",(i+1), algorithm_list[i]);
    		printf("\033[0m"); 
    	}else{
    		printf("%d. %s\n",(i+1), algorithm_list[i]);
    	}
    	
    }
    
   // for(int i=0; i<(c1.row-10); i++){printf("\n");}
    for(int i=0; i<((c1.row-7)/2); i++){printf("\n");}
    
    printf("\033[30m\033[47m");
			printf("Press ESC twice to exit.");
			for(int i=0; i<c1.col-24; i++){
				printf(" ");
			}
	printf("\033[0m");
    
   	
   	 //This code for hiding cursor in linux terminal  
   	nocur;
   	
   	int d = getch();
   	if(d==10){
   			/*cur;
   			
   			clr;
   			COR c1 = coordinate();
			for(int i=0; i<((c1.col-length(name))/2); i++){printf(" ");}
			
			printf("\033[37m\033[41m");
			printf("%s\n\n", name);
			printf("\033[0m\n");
   			if(default_select==0){
   				printf("Give random data size between [1-%d]: ", c1.col);
				scanf("%d", &size);
				fflush(stdin);
				
				random_data(size, c1.row);
				if(getch()=='\033'){
					getch();
					getch();
				}
			//	break;
   				//
   			}else if(default_select==1){
	   			printf("Give data size between [1-%d]: ", c1.col);
				
				scanf("%d", &size);
				printf("\nGive %d data between [1-%d]: ",size, c1.row-4);
				
				
				for(int i=0; i<size; i++){
					scanf("%d", &data[i]);
				}
				fflush(stdin);
				if(getch()=='\033'){
					getch();
					getch();
				}
				//break;
   			}else if(default_select==2){
   				printf("Give delay in second (Now %.1f): ", _time);
   				scanf("%f", &_time);
   				fflush(stdin);
   				if(getch()=='\033'){
					getch();
					getch();
				}
   				//break;
   			}else if(default_select==3){
   				step_mode_setup(name);
   			}else if(default_select==4) {
   				set_color(name);
   			}
   			*/
   	}
   	
  
   	
   	//This code take arrow key input in linux
   	if (d == '\033') { // if the first value is esc
   		if(getch()=='\033'){
   			printf("\e[?25h"); // This line for enable cursor
   			break;
   		} // skip the [
		switch(getch()) { // the real value
		    case 'A':
		        // code for arrow up
		        if(default_select==0){
		        	default_select=4;
		        }else{
		        	default_select--;
		        }
		        break;
		    case 'B':
		        // code for arrow down
		       
		        default_select = (default_select+1)%5;
		        break;
		}
		
		
		
	}
	}
}

void short_menu(char name[], int algo_select){
	int default_select=0;
	
	while(1){
	
	int size=0;
	clr;
	COR c1 = coordinate();
	for(int i=0; i<((c1.col-length(name))/2); i++){printf(" ");}
	
	printf("\033[37m\033[41m");
	printf("%s", name);
	printf("\033[0m");
	
	for(int i=0; i<((c1.row-8)/2); i++){printf("\n");}
	
	for(int i=0; i<((c1.col-26)/2); i++){printf(" ");}
	
	printf("Use ↑ and ↓ key to select:\n\n");
	char algorithm_list[5][22] = {"Random data set.", "Custom data set.", "Set animation delay.", "Enable step mode.", "Set color"};
  
  	
  
    int k=0;
    for(int i=0; i<5; i++){
    for(int i=0; i<((c1.col-19)/2); i++){printf(" ");}
    	if(default_select==(i)){
    		printf("\033[30m\033[47m");
    			printf("%d. %s\n",(i+1), algorithm_list[i]);
    		printf("\033[0m"); 
    	}else{
    		printf("%d. %s\n",(i+1), algorithm_list[i]);
    	}
    	
    }
    
   // for(int i=0; i<(c1.row-10); i++){printf("\n");}
    for(int i=0; i<((c1.row-7)/2); i++){printf("\n");}
    
    printf("\033[30m\033[47m");
			printf("Press ESC twice to exit.");
			for(int i=0; i<c1.col-24; i++){
				printf(" ");
			}
	printf("\033[0m");
    
   	
   	 //This code for hiding cursor in linux terminal  
   	nocur;
   	
   	int d = getch();
   	if(d==10){
   			cur;
   			
   			clr;
   			COR c1 = coordinate();
			for(int i=0; i<((c1.col-length(name))/2); i++){printf(" ");}
			
			printf("\033[37m\033[41m");
			printf("%s\n\n", name);
			printf("\033[0m\n");
   			if(default_select==0){
   				fflush(stdin);
   				printf("Give random data size between [1-%d]: ", c1.col);
				scanf("%d", &size);
				//fflush(stdin);
				
				random_data(size, c1.row);
				if(getch()=='\033'){
					getch();
					getch();
				}
			//	break;
   				//
   			}else if(default_select==1){
	   			printf("Give data size between [1-%d]: ", c1.col);
				
				scanf("%d", &size);
				printf("\nGive %d data between [1-%d]: ",size, c1.row-4);
				
				
				for(int i=0; i<size; i++){
					scanf("%d", &data[i]);
				}
				fflush(stdin);
				if(getch()=='\033'){
					getch();
					getch();
				}
				//break;
   			}else if(default_select==2){
   				printf("Give delay in second (Now %.1f): ", _time);
   				scanf("%f", &_time);
   				fflush(stdin);
   				if(getch()=='\033'){
					getch();
					getch();
				}
   				//break;
   			}else if(default_select==3){
   				step_mode_setup(name);
   			}else if(default_select==4) {
   				set_color(name);
   			}
   			
   	}
   	
  
   	
   	//This code take arrow key input in linux
   	if (d == '\033') { // if the first value is esc
   		if(getch()=='\033'){
   			printf("\e[?25h"); // This line for enable cursor
   			break;
   		} // skip the [
		switch(getch()) { // the real value
		    case 'A':
		        // code for arrow up
		        if(default_select==0){
		        	default_select=4;
		        }else{
		        	default_select--;
		        }
		        break;
		    case 'B':
		        // code for arrow down
		       
		        default_select = (default_select+1)%5;
		        break;
		}
		
		
		
	}
	
	
	
	
	if(size>0){
		clr;
		nocur;
		if(!step_mode){
			printf("Press any key to start `%s`.", name);
		}else{
			printf("Press any key to go one step.");
		}
		
		
		list_visualizer(data, size, 0);
		
		if(getch()=='\033') {
			if(getch()=='\033'){
				continue;
			}
			getch();
		}
		
		
		
		switch(algo_select){
			case 0:
				bubble_sort(data, size);
			break;
			
			case 1:
				selection_sort(data, size);
			break;
			
			case 2:
				insertion_sort(data, size);
			break;
			
			case 3:
				merge_sort(data, 0, size-1, size);
			break;
			
			
		}
		
		sorting_finish=1;
		clr;
		list_visualizer(data, size, 0);
		printf("Press any key to back.");
		if(getch()=='\033'){
			getch();
			getch();
		}
		fflush(stdin);
		sorting_finish=0;
		
	}
	
}

	
}

void go_to(char list[][20], int select){
	printf("\e[?25h"); //enable cursor
	clr;
	COR c1 = coordinate();
	
	for(int i=0; i<((c1.col-11)/2); i++){printf(" ");}
	
	printf("\033[37m\033[41m");
	printf("%s\n", list[select]);
	printf("\033[0m\n");
	
	
	short_menu(list[select], select);
	
	cur;
	
}

void show_menu(){
	int default_select=0;
	while(1){
	clr;
	COR c1 = coordinate();
	
	for(int i=0; i<((c1.col-19)/2); i++){printf(" ");}
	
	printf(" Sorting Visualizer");
	
	for(int i=0; i<(c1.row-8)/2; i++){printf("\n");}
	

		for(int i=0; i<((c1.col-26)/2); i++){printf(" ");}
	
	printf("Use ↑ and ↓ key to select:\n\n");
	char algorithm_list[10][20] = {"Bubble Sort","Selection Sort","Insertion Sort","Merge Sort","Quick Sort","Heap Sort","Counting Sort","Radix Sort","Bucket Sort","Shell Sort"};
    int mx = max_element(algorithm_list);
   
    
    
    int k=0;
    for(int i=0; i<5; i++){
    	for(int i=0; i<((c1.col-47)/2); i++){printf(" ");}
    	
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
   	
   	int d = getch();
   	if(d==10){
   			if(default_select<5){
   				go_to(algorithm_list, default_select*2);
   			}else{
   			  //5 6 7 8 9
   			  //1 3 5 7 9
   			  if(default_select==5){
   			  	go_to(algorithm_list, 1);
   			  }else if(default_select==6){
   			  	go_to(algorithm_list, 3);
   			  }else if(default_select==7){
   			  	go_to(algorithm_list, 5);
   			  }else if(default_select==8){
   			  	go_to(algorithm_list, 7);
   			  }else{
   			  	go_to(algorithm_list, 9);
   			  }
   				
   			}
   			
   	}
   	
   	
   	//This code take arrow key input in linux
   	if (d == '\033') { // if the first value is esc
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
		        if(default_select<5){
		        	default_select +=5;
		        }
		        break;
		    case 'D':
		        // code for arrow left
		        if(default_select>=5){
		        	default_select -=5;
		        }
		        break;
		}
		
		
		
	}
	
	
	
   
    }
    
    
   
}

int main(int argc, char **argv){
	
	//intro_page();
	//sleep(1);
	show_menu();

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


