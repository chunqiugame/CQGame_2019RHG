#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

char sf[]="WSWSADADBABA";

int game(char *buf){
	char *p=buf;
	char buff[0x20]={0};
	for(;*p!=0;p++){
		switch(*p){
			case 'W':strcat(buff,"W");break;
			case 'A':strcat(buff,"A");break;
			case 'S':strcat(buff,"S");break;
			case 'D':strcat(buff,"D");break;
			case 'B':strcat(buff,"B");break;
			default:break;
		}
	}
	return !strcmp(buff,sf);
}


void run(){
	char buf[0x20];
	read_n(buf,0x10);
	if(game(buf)){
		system("/bin/sh");
	}
}

int main(void) {
    PWNINIT
    run();
}
