#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

char* g_list[0x10] = {0};
char name[48] = {0};
char buff[0x200];
int read_n(char *buf, unsigned long size){
    int result;
    result = read(0, buf, size - 1);
    buf[size - 1] = '\x00';
    return result;
}

void init(){
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}


int add(){
    unsigned long size, i;
    char *chunk;
    scanf("%lu", &size);
    getchar();
    chunk = malloc(size);
    read_n(chunk, size);
    for(i = 0; i < 0x10; ++i){
        if(g_list[i] == NULL)
            break;    
    }
    if(i != 0x10)
        g_list[i] = chunk;
    else{
        exit(0);
    }
    return 0;
}

int delete(){
    int idx;
    scanf("%d", &idx);
    getchar();
    if(idx < 0 || idx >= 0x10){
        return -1;
    }
    free(g_list[idx]);
    // UAF will happen here
    //g_list[idx] = NULL;
    return 0;
}

int edit(){
    int idx;
    scanf("%d", &idx);
    getchar();
    if(idx < 0 || idx >= 0x10){
        return -1;
    }
    int size = strlen(g_list[idx]); // cant success every time
    read_n(g_list[idx], 0x20);
    read_n(name, 48);
    return 0;
}

int main(){
    int choice;
    init();
    /* 1. add
       2. delete
       3. edit
       4. exit
    */
    while(1){
        scanf("%d", &choice);
        getchar();
        switch(choice){
            case 1:
                    add();
                    break;
            case 2:
                    delete();
                    break;
            case 3:
                    edit();
                    break;
            default:
                    break; 
        }
    }
    return 0;
}

