#include "matrix.h"
#include "common.h"
#include <stdlib.h>

Matrix *matrix_new() {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    if(matrix == NULL)
        return NULL;
    
    matrix->max_col  = INI_MATRIX_COL;
    matrix->max_row  = INI_MATRIX_ROW;
    matrix->curr_col = 0;
    matrix->curr_row = 0;
    matrix->len      = matrix->max_col * matrix->max_row;
    matrix->data     = (Blucket**)malloc(matrix->len * sizeof(Blucket*));
    if(matrix->data == NULL) {
        free(matrix);
        return NULL;
    }
    
    return matrix;
}

int matrix_add(Matrix *matrix, Element *element) {
    unsigned index = element->col * element->row;
    if(index >= matrix->len) {
        int res = matrix_realloc(matrix);
        if(res != 0)
            return NULL;
    }
    
    Blucket *blucket = matrix->data[index]
    if(blucket == NULL) {
        Blucket *_blucket = blucket_new();
        if(_blucket == NULL)
            return NULL;
        else
            matrix->data[index] = _blucket;
    } else {
        
    }
        
}