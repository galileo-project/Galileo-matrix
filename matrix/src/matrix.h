#include "common.h"
#include "element.h"

#ifndef MATRIX_MATRIX_H_
#define MATRIX_MATRIX_H_

typedef struct matrix_s {
    unsigned max_col;
    unsigned max_raw;
    unsigned max_len;
    unsigned curr_col;
    unsigned curr_row;
    unsigned curr_len;
    Blucket **data;
} Matrix;

//functions of matrix
Matrix *matrix_new();
Status matrix_init(Matrix*);
Status matrix_add(Matrix*, Element*);
Status matrix_update(Matrix*, Element*);
Status matrix_clear(Matrix*);
Element *matrix_find_by_pos(Matrix*, unsigned, unsigned);
Element *matrix_find_by_val(Matrix*, int);
unsigned hash_generator(Element*, Matrix*);
#endif //MATRIX_MATRIX_H_
