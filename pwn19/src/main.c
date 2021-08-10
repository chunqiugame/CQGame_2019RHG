#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int read_n(char *buffer, int buf_size) {
    int i, result;
    for (i = 0; i < buf_size - 1; i++) {
        result = (int) read(STDIN_FILENO, buffer + i, 1);
        if (result != 1) {
            exit(1);
        } else if (buffer[i] == '\n') {
            break;
        }
    }
    buffer[i] = 0;
    return i;
}

int read_int(){
    char buffer[32] = {0};
    read_n(buffer, 32);
    return atoi(buffer);
}

long read_long(){
    char buffer[32] = {0};
    read_n(buffer, 32);
    return atol(buffer);
}

void pwn_init(){
	setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
    alarm(300);
}

void puts_menu(){
    puts("1.add");
    puts("2.show");
    puts("3.delete");
    puts("4.edit");
    printf("choice >>");
}

struct node
{
	void * nonono;
	void * content;
};
char buf[0x220];
void *fake[2];
struct node *note_list[32];

void add(){
	int idx;
    for (idx=0;note_list[idx]&&idx<32;idx++);
    if(idx >= 32){
        puts("Not any more !!");
        return;
    }
    printf("size:");
    int size;
    size = read_int();
    if(size < 0 || size > 0x100){
    	puts("Invalid size!");
    	return;
    }
 	void * tmp = (void *)malloc(size);
 	if(!tmp){
 		puts("Malloc error!");
 		exit(-1);
 	}
 	printf("content:");
 	read_n(tmp,size);
 	struct node* n = malloc(sizeof(struct node));
 	if(!n){
 		puts("Malloc error!");
 		exit(-1);
 	}
 	n->content = tmp;
 	note_list[idx] = n;
 	puts("Add done!");
}

void show(){
	int idx;
	printf("id:");
	idx = read_int();
	if(idx < 0||idx > 31||!note_list[idx]){
		puts("Invalid id!");
		return;
	}
	printf("Your data:%s\n",note_list[idx]->content);
}

void delete(){
	int idx;
	printf("id:");
	idx = read_int();
	if(idx < 0||idx > 31||!note_list[idx]){
		puts("Invalid id!");
		return;
	}
	free(note_list[idx]->content);
	free(note_list[idx]);
}

void edit(){
    int idx;
    printf("id:");
    idx = read_int();
    if(idx < 0||idx > 31||!note_list[idx]){
        puts("Invalid id!");
        return;
    }
    printf("size:");
    long size;
    size = read_long();
    printf("content:");
    read_n(note_list[idx]->content,size);
}

int main(int argc, char const *argv[])
{
    fake[0] = 0;fake[1] = 0x39;
	pwn_init();
	int op;
	while(1){
		puts_menu();
		op = read_int();
		switch(op){
            case 1:
                add();
                break;
            case 2:
                show();
                break;
            case 3:
            	delete();
            	break;
            case 4:
                edit();
                break;
            default:
                puts("Invalid Choice !");
                return 0;
        }
	}
	return 0;
}