#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "pwnInit.h"
#include "unit.h"
#include "func.h"

void run() {
    char buf[0x10];
    func1(1);
    puts("GOOD");
    read_n(buf, 0x100);
}

int main(void) {
    PWNINIT
    run();
}
