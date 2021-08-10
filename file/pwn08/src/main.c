#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

int boss=0;

void run(){
	char buf[0x100]={0};
	read_n(buf,0x88);
	for(int i=0;i<0x88;i++){
		buf[i]^=0x88;
	}
	printf(buf);
	if(boss==0x8888){
		system("/bin/sh");
	}
}

int main(void) {
    PWNINIT
    run();
}
