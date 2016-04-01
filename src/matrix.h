#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

#include "common.h"
#include "element.h"

typedef struct matrix_s {
    unsigned max_col;
    unsigned max_raw;
    unsigned curr_col;
    unsigned curr_row;
    unsigned len;
    Blucket **data;
} Matrix;

//functions of matrix
Matrix *matrix_new();
Status matrix_realloc(Matrix*);
Status matrix_add(Matrix*, Element*);
Status matrix_update(Matrix*, Element*);
Status matrix_status(Matrix*);
Status matrix_clear(Matrix*);
Element *matrix_find(Matrix*);

#endif //MATRIX_MATRIX_H_