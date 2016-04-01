#include "matrix.h"
#include "common.h"
#include <stdlib.h>

Matrix *matrix_new() {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    if(matrix == NULL)
        return NULL;
    
    matrix->max_col = INI_MATRIX_COL;
    matrix->max_row = INI_MATRIX_ROW;
    matrix->curr_col = 0;
    matrix->curr_row = 0;
    
    return matrix;
}

void matrix_init(Matrix *matrix) {
    
}