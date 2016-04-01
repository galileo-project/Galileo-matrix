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

Status matrix_add(Matrix *matrix, Element *element) {
    unsigned index = element->col * element->row;
    if(index >= matrix->len) {
        Status res = matrix_realloc(matrix);
        if(res != STAT_SUCCESS)
            return res;
    }
    
    Blucket *blucket;
    if(matrix->data[index] == NULL) {
        blucket = blucket_new();
        if(blucket == NULL)
            return STAT_NEW_BLU_ERR;
        else
            matrix->data[index] = blucket;
    } else {
        blucket = matrix->data[index];
    }
    
    return blucket_add(blucket, element);
}

