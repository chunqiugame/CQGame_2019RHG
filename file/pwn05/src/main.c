#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

unsigned int canary=0x90909090;

void func(){
	__asm__ __volatile__("jmp %%esp":::);
}

void run(){
	unsigned int c1=canary;
    char buff[0x10];
    read_n(buff,0x100);
    if(c1^canary){
    	exit(0);
    }
}

int main(void) {
    PWNINIT
    run();
}
