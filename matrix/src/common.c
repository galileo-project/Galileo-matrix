#include "common.h"
#include <stdlib.h>

void safe_free(void *p) {
    if(p != NULL)
        free(p);
}