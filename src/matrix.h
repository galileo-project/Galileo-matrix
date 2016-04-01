#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

#include "common.h"
#include "element.h"

typedef struct matrix_s {
    unsigned max_col;
    unsigned max_raw;
    Element **data;
} Matrix;

//functions of matrix
Matrix matrix_new();
void matrix_init(Matrix*);

#endif //MATRIX_MATRIX_H_