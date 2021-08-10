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
    char buff[0x10];
    read_n(buf,0x100);
    read_n(buff,0x21);
}

int main(void) {
    PWNINIT
    run();
}
