#ifndef PC_H
#define PC_H

#include <stdio.h>
#include "uso.h"

void write_in_c() {
    printf("write_in_c\n");
}

void pc() {
    write_in_c();
    compile();
    run();
}
#endif
