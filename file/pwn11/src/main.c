#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

void run(){
	int len;
	char buf[0x20];
	scanf("%d", &len);
	if(len<0x20)
		read_n(buf, len);
	else
		exit(0);
}

int main(void) {
    PWNINIT
    run();
}
