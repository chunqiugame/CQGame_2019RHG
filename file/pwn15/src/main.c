#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

char buf[0x111];
void (*func)();

void run(){
	
	int len;
	len=read_n(buf,0x100);
	for(int i=0;i<len;i++)
		buf[i]^=i;
	func=&buf;
	(*func)();
}

int main(void) {
    PWNINIT
    run();
}