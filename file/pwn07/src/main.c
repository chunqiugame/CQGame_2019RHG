#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

int i=0;

void run(){
	char buf[0x100]={0};
	read_n(buf,0x100);
	printf(buf);
	if(i==0x8888){
		system("/bin/sh");
	}
}

int main(void) {
    PWNINIT
    run();
}
