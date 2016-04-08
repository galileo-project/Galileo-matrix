#include "matrix.h"
#include "element.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//config
Config *config_new(unsigned row, unsigned col) {
    Config *config = (Config*)malloc(sizeof(Config));
    if(config == NULL)
        return NULL;
    
    config->max_col = col;
    config->max_row = row;
    
    return config;
}

Matrix *matrix_new(Config *config) {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    if(matrix == NULL)
        return NULL;
    
    matrix->max_col  = config->max_col;
    matrix->max_row  = config->max_row;
    matrix->max_len  = matrix->max_col * matrix->max_row;
    matrix->curr_col = 0;
    matrix->curr_row = 0;
    matrix->curr_len = 0;
    matrix->data     = (Blucket**)malloc(matrix->max_len * sizeof(Blucket*));
    if(matrix->data == NULL) {
        safe_free(matrix);
        return NULL;
    }
    for(unsigned i = 0; i < matrix->max_len; i++)
        matrix->data[i] = blucket_new();
    
    return matrix;
}


Status matrix_add(Matrix *matrix, Element *element) {
    unsigned index = hash_generator(element->row, element->col, matrix);
    if(index >= matrix->max_len) {
        return STAT_MAX_MATRIX_LEN_ERR;
    }
    
    //Update curr index
    matrix->curr_len ++;
    if(element->row > matrix->curr_row)
        matrix->curr_row = element->row;
    if(element->col > matrix->curr_col)
        matrix->curr_col = element->col;
        
    return blucket_add(matrix->data[index], element, False);
}

Status matrix_update(Matrix *matrix, Element *element) {
    unsigned index = hash_generator(element->row, element->col, matrix);
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
    
    return STAT_SUCCESS;
}

Element *matrix_find_by_pos(Matrix *matrix, unsigned row, unsigned col) {
    unsigned index = hash_generator(row, col, matrix);
    return blucket_seek_by_pos(matrix->data[index], row, col);
}

Element *matrix_find_by_val(Matrix *matrix, int value) {
    unsigned index;
    Element *element;
    for(index = 0; index < matrix->max_len; index++) {
        element =  blucket_seek_by_val(matrix->data[index], value);
        if(element != NULL)
            return element;
    }
    return NULL;
}

unsigned hash_generator(unsigned row, unsigned col, Matrix *matrix) {
    //TODO update hash generator
    return (row * col);
}

Status matrix_expand(Matrix* matrix) {
    //TODO implement
    return STAT_SUCCESS;
}

Matrix *array_to_matrix(int *array, unsigned row, unsigned col) {
    //TODO implement
    return NULL;
}

Status matrix_print(Matrix* matrix) {
    Element *element;
    int res;
    
    printf("%4s   ", "");
    for(unsigned col = 0; col < matrix->curr_col; col++) {
        printf("%4d", col);            //print col index
    }
    printf("\n");
    
    for(unsigned row = 0; row < matrix->curr_row; row++) {
        printf("%4d | ", row);         //print row index
        for(unsigned col = 0; col < matrix->curr_col; col++) {
            element = matrix_find_by_pos(matrix, row, col);
            if(element == NULL)
                res = 0;
            else
                res = element->value;
                         
            printf("%4d", res);
        }
        printf("  |\n");
    }
    
    return STAT_SUCCESS;
}