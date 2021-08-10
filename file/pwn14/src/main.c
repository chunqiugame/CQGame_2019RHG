#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

/*
请求

MREAD 0x00000000 RHG/1.0ED    0x00000000 - 0xffffffff
USER-AGENT:Robot/1.0ED        Robot / Human
TIME:20190624ED               2019-2020
ACCEPT:HexED                  Hex/Dec/Oct/Bin
RETURN-LENGTH:0x100ED         0< len < 0x10000


WRITE 0x080BE4E0 RHG/1.0EDUSER-AGENT:Robot/1.1EDTIME:1546272001EDACCEPT:HexEDRETURN-LENGTH:0x100ED



响应
RHG/1.0 200 OKED
SERVER:C-NCED
TIME:1546272001ED
RESPONSE:0
RETURN:AAAAAAAAAAAAA

*/
#define STATUS 0
#define ADDR 1
#define RACE 2
#define TIME 3
#define DEC 4
#define LEN 5

char data[0x1000];
//                read/write        addr   race        time   decimal   len
unsigned int ss[]={       0, 0x00000000,     0, 1546272001,        0, 0x100};

const char version[]="RHG/1.0";
const char ua[]="USER-AGENT";
const char tm[]="TIME";
const char ac[]="ACCEPT";
const char rl[]="RETURN-LENGTH";

const char status[][0x10]={"MREAD","WRITE"};
const char race[][0x10]={"Human/1.0","Robot/1.1"};
const char decimal[][0x10]={"Hex","Dec","Oct","Bin"};

const unsigned int timestamp[2]={1546272000,1577808000};

void itoa(int n,char *buf){
	sprintf(buf,"%d",n);
}
void responseProtocol(int code,char *content){
	char codes[0x10]={0};
	char time[0x10]={0};
	char dec[0x10]={0};

	char buff[5][0x1010]={
		"RHG/1.0 ",
		"SERVER:C-NCED",
		"TIME:",
		"RESPONSE:",
		"RETURN:"
	};
	itoa(code,codes);
	itoa(ss[3],time);
	itoa(ss[4],dec);
	if(code/100==2){
		strcat(codes," OK");
	}
	else{
		strcat(codes," ERROR");
	}
	strcat(buff[0],codes);
	strcat(buff[0],"ED");

	strcat(buff[2],time);
	strcat(buff[2],"ED");

	strcat(buff[3],dec);
	strcat(buff[3],"ED");

	strcat(buff[4],content);
	strcat(buff[4],"ED");
	for(int i=0;i<5;i++){
		printf("%s",buff[i]);
	}
	puts("");
}

int getPart(char *buf,char *buf1){
	int i=0;
	for(;(buf[i]!='E' || buf[i+1]!='D');i++){
		buf1[i]=buf[i];
	}
	buf1[i]=0;
	return i;
}

void strCMP(const char *str1,char *str2,const char *content){
	if(strcmp(str1,str2)){
		//puts(str1);
		//puts(str2);
		responseProtocol(444,(char *)content);
		exit(0);
	}
}

void strCMP1(const char str1[][0x10],char *str2,const char *content,int time){
	int n=0;
	for(int i=0;i<time;i++)
		if(!strcmp(str1[i],str2))
			n=1;
	if(!n){
		responseProtocol(444,(char *)content);
		exit(0);
	}
}

void checkProtocol(char *buf){
	int j;
	char a1[0x10]={0},b1[0x10]={0};
	unsigned int c1;
	for(j=0;buf[j]!='\0';j++)
		if(buf[j]==':')
			buf[j]=' ';
	//puts(buf);
	switch(buf[0]){
		case 'M':
		case 'W':
			sscanf(buf,"%s %x %s",a1,&c1,b1);
			strCMP1(status,a1,"HEAD ERROR",2);
			strCMP(version,b1,"VERSION ERROR");
			if(buf[0]=='M')
				ss[0]=0;
			else
				ss[0]=1;
			ss[1]=c1;
			break;
		case 'U':
			sscanf(buf,"%s %s",a1,b1);
			strCMP(ua,a1,"USER-AGENT ERROR");
			strCMP1(race,b1,"RACE ERROR",2);
			if(!strcmp(b1,"Robot"))
				ss[2]=0;
			else
				ss[2]=1;
			break;
		case 'T':
			sscanf(buf,"%s %d",a1,&c1);
			strCMP(tm,a1,"TIME ERROR");
			if(c1<timestamp[0] || c1>timestamp[1]){
				responseProtocol(444,"TIMESTAMP ERROR");
				exit(0);
			}
			ss[3]=c1;
			break;
		case 'A':
			sscanf(buf,"%s %s",a1,b1);
			strCMP(ac,a1,"ACCEPT ERROR");
			strCMP1(decimal,b1,"DECIMAL ERROR",4);
			switch(b1[0]){
				case 'H':ss[4]=0;break;
				case 'D':ss[4]=1;break;
				case 'O':ss[4]=2;break;
				case 'B':ss[4]=3;break;
				default:responseProtocol(444,"ERROR");exit(0);break;
			}
			break;
		case 'R':
			sscanf(buf,"%s %x",a1,&c1);
			strCMP(rl,a1,"RETURN-LENGTH ERROR");
			if(c1<1 && c1>0x1000){
				responseProtocol(444,"LEN ERROR");
				exit(0);
			}
			ss[5]=c1;
			break;
		default:responseProtocol(444,"CHECK ERROR");break;
	}
}

int getProtocol(){
	char buf[0x10]={0};
	int len;
	char reHead[0x500]={0};
	char head[5][0x100]={0};
	read_n(reHead,0x400);
	if(!strcmp(reHead,"EXIT")){
		responseProtocol(200,"Please Input:");
		read_n(buf,0x30);
		return 1;
	}
	memset(head,0,0x500);
	len=getPart(reHead,head[0])+2;
	len+=getPart(reHead+len,head[1])+2;
	len+=getPart(reHead+len,head[2])+2;
	len+=getPart(reHead+len,head[3])+2;
	len+=getPart(reHead+len,head[4])+2;
	for(int i=0;i<5;i++){
		checkProtocol(head[i]);
	}
	return 0;
}

void run(){
	char *buf;
	while(1){
		if(getProtocol())
			break;
		if(!ss[0]){
			buf=(char *)malloc(ss[LEN]+0x10);
			memset(buf,0,LEN+0x10);
			for(int i=0;i<ss[LEN];i++){
				buf[i]=*(char *)(ss[ADDR]+i);
			}
			responseProtocol(200,buf);
			free(buf);
		}
		else{
			buf=(char *)malloc(ss[LEN]+0x10);
			responseProtocol(200,"Please Input:");
			int len=read_n(buf,ss[LEN]);
			memcpy((char *)ss[ADDR],buf,len);
			responseProtocol(200,"OK");
		}
	}
}

int main(void) {
    PWNINIT
    memset(data,0,0x1000);
    run();
}