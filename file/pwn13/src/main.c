#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

void func(){
	__asm__ __volatile__("jmp %%esp":::);
}

unsigned int getPasswd(){
	int fp;
	unsigned int num;
	fp=open("/dev/urandom",0);
	read(fp,&num,2);
	num&=0xffff;
	return num;
}

void run(){
	char buf[0x10];
	unsigned int pwd;
	while(1){
		pwd=read_int();
		if(pwd==getPasswd()){
			close(100);
			puts("Congratulation");
			read_n(buf,0x100);
			return ;
		}
		puts("No, Please continue");
	}
}

int main(void) {
    PWNINIT
    run();
}