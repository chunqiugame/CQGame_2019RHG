#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

char buf[0x100];

void run(){
	char buff[0x50];
	while(1){
		read_n(buff,0x4c);
		if(!strcmp(buff,"EXIT")){
			break;
		}
		printf(buff);
	}
	return ;

}

int main(void) {
    PWNINIT
    run();
}
