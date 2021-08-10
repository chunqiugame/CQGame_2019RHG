import random

func = '''
void func%d(int num) {
    unsigned int i;
    if (num != %d) {
        exit(0);
    }
    void (*func)(int);
    i = (unsigned int) read_int();
    if (i < 20000) {
        func = func_array[i];
        func(num + 1);
    }
}
'''

func_code = '''
#include <stdlib.h>
#include "func.h"
#include "unit.h"

%s
'''

funcs = ''
for i in range(20000):
    funcs += func%(i+1, i+1)

with open("./func.c", 'w') as fp:
    fp.write(func_code%funcs)


func_head = '''
#ifndef SRC_FUNC_H
#define SRC_FUNC_H

%s

%s

#endif //SRC_FUNC_H
'''


func_def = 'void func%d(int num);\n'

func_defs = ''

for i in range(20000):
    func_defs += func_def%(i+1)

func_arr = 'void *func_array[] = {%s};'

a = [i+1 for i in range(20000)]
random.shuffle(a)

fs = ''

for i in range(20000):
    i = a.index(i+1) + 1
    fs += "func%d, "%i


with open("./func.h", 'w') as fp:
    fp.write(func_head%(func_defs, func_arr%fs))

print a
