#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"

struct note{
    int size;
    char *name;
};


struct note* g_notes[32] = {0x41};
char buf[0x200];
void menu() {
    puts("1. add note");
    puts("2. delete note");
    puts("3. edit a note");
    puts("x. quit");
    puts("choice: ");
}

void add(){
    struct note *p;
    char *buf;
    int index, size;
    printf("size:");
    scanf("%d", &size);
    getchar();
    buf = malloc(size); // memory leakage here ... we can input a bigger index to make it not being used...
    printf("content:");
    read_n(buf, size);
    printf("index:");
    scanf("%d", &index);
    getchar();
    if (index >= 32) {
        puts("The place is out of bound.");
        return;
    }
    p = malloc(sizeof(struct note));
    p->name = buf;
    p->size = size;
    g_notes[index] = p;
    puts("add success");
}

void del(){
    int index;
    puts("index:");
    scanf("%d", &index);
    getchar();
    if (index >= 32) {
        puts("The place is out of bound.");
        return;
    }
    if(!g_notes[index]){
        puts("There is no note here");
        return;
    }
    // free the buffer 
    free(g_notes[index]->name);
    free(g_notes[index]);
    // g_notes[index] = 0;
    puts("delete success");
}

void edit(){
    int index;
    int size;
    puts("plz tell me the index of note");
    scanf("%d", &index);
    getchar();
    if (index >= 32) {
        puts("The place is out of bound.");
        return;
    }
    if(!g_notes[index]){
        puts("There is no note here");
        return;
    }
    puts("plz give my note size");
    size=read_int();
    puts("plz give my note content");
    read_n(g_notes[index]->name, size);
    puts("edit success");
}

int main(void) {
    PWNINIT
    int choose;
    while (1) {
        menu();
        choose = read_int();
        switch (choose) {
            case 1:
                add();
                break;
            case 2:
                del();
                break;
            case 3:
                edit();
                break;
            default:
                return 0;
        }
    }


}

