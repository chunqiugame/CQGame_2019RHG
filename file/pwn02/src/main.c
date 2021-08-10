#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"
volatile unsigned char *p;
void func(){
	__asm__ __volatile__("jmp %%esp":::);
}

void run(){
    char buf[0x10];
    gets(buf);
    p=(buf+0x22);
    if(*p!=0x90){
        //printf("1 %hhu %hhu\n",*p,*(buf+0x22));
        exit(0);
    }
    p=(buf+0x28);
    if(*p!=0x90){
        //printf("2 %hhu %hhu\n",*p,*(buf+0x22));
        exit(0);
    }
}

int main(void) {
    PWNINIT
    run();
}
