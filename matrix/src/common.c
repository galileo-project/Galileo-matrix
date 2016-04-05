#include "common.h"
#include <stdlib.h>

void safe_free(void *p) {
    if(p != NULL)
        free(p);
}

unsigned hash_generator(unsigned row, unsigned col, unsigned len) {
    
}