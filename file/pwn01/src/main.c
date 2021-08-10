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
void run(){
    char buf[0x10];
    gets(buf);
}

int main(void) {
    PWNINIT
    run();
}
