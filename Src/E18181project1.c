#include <stdio.h> //include essential libraries.
#include <time.h>
#include <unistd.h>
#include<stdlib.h>
#include<signal.h>

//declare the functions
int *getTime();
void runclock();
void color(int);
void reset();
int selectcolor();
int printnum(int);
void terminate(int);

//global variables and arrays use in whole program.
int TIME[6];
int n=9;
int i;
char COLOR_[10];

int main(int argc,char *argv[]){
	if(argc==1){ //argument1----> default
		n=9;
	}
	else if(argc==2){
		if((argv[1][0]=='-')&&(argv[1][1]=='h')){ //argument2----> '-h':help.
			printf("usage: clock -h           quick help on cmd\n");
			printf("usage: clock -c <color>   print clock with a color\n");
			printf("<color -black|red|green|yellow|blue|magenta|cyan|white> supported colors\n");
			return 0;
		}
		else if(argv[1][0]=='-'){ //argument2----> '-(any letter)':ERROR HANDLING. 
			printf("Invalid use of arguments.\n");
			printf("usage: clock -h           quick help on cmd\n");
			printf("usage: clock -c <color>   print clock with a color\n");
			return 0;
		}
		else{
			n=9; //argument----> default
		}


	}
	else{ //more than 3arguments
		if((argv[1][0]=='-')&&(argv[1][1]=='c')){ //check the second argument. 
			for(i=0;argv[2][i]!='\0';i++){   //convert 3rd argument to lowercase. 
				if((argv[2][i]>64)&&(argv[2][i]<91)){ 
					COLOR_[i]=argv[2][i]+32;
				}
				else{
					COLOR_[i]=argv[2][i];
				}

			}
			COLOR_[i]='\0';
			int num;
			num=selectcolor(); //call select color funtion.
			if(num!=-1){
				n=num;
			}
			else{ //ERROR HANDLING.
				printf("%s :This is not a valid color, Please enter these colors: balck, red, green, yellow, blue, magenta, cyan, white\n",argv[2]);
				return 0;
			}
		}
		else{ //ERROR HANDLING.
			printf("%s :This is not a valid color, Please enter these colors: black, red, green, yellow, blue, magenta, cyan, white \n",argv[2]);
			return 0;
		}
	}
	getTime(); //call get time funtion.
	signal(SIGINT,terminate); //behave as we want after terminate the running programm
	runclock(); //call the runclock funtion to start clock
	return 0; 
}

//function to get the current system time.
int *getTime(){
    time_t t = time(NULL); //get the system time as a integer.
    struct tm tm = *localtime(&t);

    //store them in an array.
    TIME[0]=tm.tm_sec;
    TIME[1]=tm.tm_min;
    TIME[2]=tm.tm_hour;
    TIME[3]=tm.tm_mday;
    TIME[4]=tm.tm_mon+1;
    TIME[5]=tm.tm_year+1900;

    return TIME;
}

//funtion torun the clock and print the current system time.
void runclock(){
    int year,mon,day,hour,min,sec;
    int hour1,hour2,min1,min2,sec1,sec2;

    sec=TIME[0];
    min=TIME[1];
    hour=TIME[2];
    day=TIME[3];
    mon=TIME[4];
    year=TIME[5];

    //start to run clock.
    while(1){
        sec++;
        if(sec>59){
            min++;
            sec=0;
        }
        if(min>59){
            hour++;
            min=0;
        }
        if(hour>23){		
            hour=0;
        }
        sleep(1);

        hour2=hour%10;
        hour1=hour/10;

        min2=min%10;
        min1=min/10;

        sec2=sec%10;
        sec1=sec/10;

	printf("\033[1J"); //clear above.
        printf("\033[H"); //move cursor to (0,0)
        printf("\033[1B"); //move cursor down by 1 line.
        printf("\033[1C"); //move cursor right by 1 line.
        color(n);

	//print the clock
        printnum(hour1);
        printf("\033[5A\033[1C");
        printnum(hour2);
        printf("\033[5A\033[1C");
        printnum(10);
        printf("\033[5A\033[1C");
        printnum(min1);
        printf("\033[5A\033[1C");
        printnum(min2);
        printf("\033[5A\033[1C");
        printnum(10);
        printf("\033[5A\033[1C");
        printnum(sec1);
        printf("\033[5A\033[1C");
        printnum(sec2);

	//print the date
	printf("\033[1B");
        printf("\033[25G");
        printf("%04d-%02d-%02d\n",year,mon,day);
    }
}

//function to assign colors to printed characters.
void color(int n){
    if(n==0){
        printf("\033[0;30m");
    }
    else if(n==1){
        printf("\033[0;31m");
    }
    else if(n==2){
        printf("\033[0;32m");
    }
    else if(n==3){
        printf("\033[0;33m");
    }
    else if(n==4){
        printf("\033[0;34m");
    }
    else if(n==5){
        printf("\033[0;35m");
    }
    else if(n==6){
        printf("\033[0;36m");
    }
    else{
        printf("\033[0;39m");
    }
}

//function to reset the color to default color.
void reset(){
	printf("\033[0m");
}

//funtion to identify the user input color.
int selectcolor(){
	char colors_[7][8]={"black","red","green","yellow","blue","magenta","cyan"}; //find the color and return last integer value allocated for each color.
	for(int j=0;j<7;j++){
		int l;
		for(l=0;colors_[j][l]!='\0';){
			l++;
		}

		if(i==l){
			int m=0;
			for(int k=0;k<i;k++){
				if(COLOR_[k]==colors_[j][k]){
					m++;
				}
				else{
					break;
				}
			}

			if(m==l){
				return j;
			}
			else{}
		}
		else{
			continue;
		}
	}
	return -1;
}

//funtion to print large numbers.
int printnum(int num){
	if(num==0){
        printf("██████\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██████\033[1B");
	}

	else if(num==1){
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B");
	}

	else if(num==2){
        printf("██████\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("██████\033[1B\033[6D");
        printf("██    \033[1B\033[6D");
        printf("██████\033[1B");
	}

	else if(num==3){
        printf("██████\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("██████\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("██████\033[1B");
	}

	else if(num==4){
        printf("██  ██\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██████\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B");
	}

	else if(num==5){
        printf("██████\033[1B\033[6D");
        printf("██    \033[1B\033[6D");
        printf("██████\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("██████\033[1B");
	}

	else if(num==6){
        printf("██████\033[1B\033[6D");
        printf("██    \033[1B\033[6D");
        printf("██████\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██████\033[1B");
	}

	else if(num==7){
        printf("██████\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("    ██\033[1B");
	}

	else if(num==8){
        printf("██████\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██████\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██████\033[1B");
	}

	else if(num==9){
        printf("██████\033[1B\033[6D");
        printf("██  ██\033[1B\033[6D");
        printf("██████\033[1B\033[6D");
        printf("    ██\033[1B\033[6D");
        printf("██████\033[1B");
	}

    	else{
        printf("      \033[1B\033[6D");
        printf("  ██  \033[1B\033[6D");
        printf("      \033[1B\033[6D");
        printf("  ██  \033[1B\033[6D");
        printf("      \033[1B");
	}
	return 0;
}


void terminate(int n){
	reset();
	printf("\033[1J");
	printf("\033[H");
	exit(1);
}

