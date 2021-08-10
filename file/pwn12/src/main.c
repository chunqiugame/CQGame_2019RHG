#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

void getPasswd(char *buf){
	int fp;
	fp=open("/dev/urandom",0);
	read(fp,&buf,8);
	close(fp);
}

void run(){
	char pwd1[0x10]={0};
	char pwd2[0x10]={0};
	getPasswd(pwd1);
	gets(pwd2);
	if(!strcmp(pwd1,pwd2))
		system("/bin/sh");
	else
		exit(0);

}

int main(void) {
    PWNINIT
    run();
}
