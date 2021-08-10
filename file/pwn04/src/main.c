#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

char buf[0x100];

void game(){
	char buff[0x10];
	read(0,buff,0x1c);
}
void run(){
    read_n(buf,0x100);
    game();
}

int main(void) {
    PWNINIT
    run();
}
