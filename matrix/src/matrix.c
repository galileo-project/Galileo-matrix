#include "matrix.h"
#include <stdlib.h>

Matrix *matrix_new() {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    if(matrix == NULL)
        return NULL;
    
    matrix->max_col  = INI_MATRIX_COL;
    matrix->max_raw  = INI_MATRIX_RAW;
    matrix->max_len  = matrix->max_col * matrix->max_raw;
    matrix->curr_col = 0;
    matrix->curr_raw = 0;
    matrix->curr_len = 0;
    matrix->data     = (Blucket**)malloc(matrix->max_len * sizeof(Blucket*));
    if(matrix->data == NULL) {
        safe_free(matrix);
        return NULL;
    }
    
    return matrix;
}

Status matrix_init(Matrix *matrix) {
    matrix->max_col  = INI_MATRIX_COL;
    matrix->max_raw  = INI_MATRIX_RAW;
    matrix->max_len  = matrix->max_col * matrix->max_raw;
    matrix->curr_col = 0;
    matrix->curr_raw = 0;
    matrix->curr_len = 0;
    
    if(matrix->data != NULL)
        safe_free(matrix->data);
    matrix->data = (Blucket**)malloc(matrix->max_len * sizeof(Blucket*));
    if(matrix->data == NULL)
        return STAT_INIT_MATRIX_ERR;
    else
        return STAT_SUCCESS;
}

Status matrix_add(Matrix *matrix, Element *element) {
    unsigned index = hash_generator(element->raw, element->col, matrix);
    if(index >= matrix->max_len) {
        return STAT_MAX_MATRIX_LEN_ERR;
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
    
    return blucket_add(blucket, element, False);
}

Status matrix_update(Matrix *matrix, Element *element) {
    unsigned index = hash_generator(element->raw, element->col, matrix);
    return blucket_add(matrix->data[index], element, True);
}

Status matrix_clear(Matrix* matrix) {
    unsigned i;
    Blucket *blucket;
    Status status;
    
    for(i=0; i < matrix->max_len; i++) {
        blucket = matrix->data[i];
        if(blucket == NULL) {
            continue;
        } else {
            status = blucket_free(blucket);
            if(status != STAT_SUCCESS)
                return status;
            else
                continue;
        }
    }
    
    return matrix_init(matrix);
}

Element *matrix_find_by_pos(Matrix *matrix, unsigned raw, unsigned col) {
    unsigned index = hash_generator(raw, col, matrix);
    return element_seek_by_pos(matrix->data[index], raw, col);
}

Element *matrix_find_by_val(Matrix *matrix, int value) {
    unsigned index;
    Element *element;
    for(index = 0; index < matrix->curr_len; index++) {
        element =  element_seek_by_val(matrix->data[index], value);
        if(element != NULL)
            return element;
        else
            continue;
    }
    return NULL;
}

unsigned hash_generator(unsigned raw, unsigned col, Matrix *matrix) {
    
}