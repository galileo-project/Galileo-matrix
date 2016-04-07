#include <stdio.h>
#include "common.h"
#include "matrix.h"
#include "element.h"

const unsigned TEST_RAW_LEN = 100;
const unsigned TEST_COL_LEN = 100;

typedef int (*Func)(void);

static Matrix *new_matrix();
int test_new_matrix(void);
int test_new_element(void);
int test_matrix_add_element(void);
int test_config_new();

int main() {
    Func functions[] = {&test_new_matrix, 
                        &test_new_element,
                        &test_matrix_add_element};
    unsigned len = sizeof(functions)/sizeof(Func);
    
    for(int i = 0; i < len; i++) {
        int res = (*functions[i])();
        if(res != 0)
            return res;
        else
            continue;
    }
                                 
    return 0;
}

int test_config_new() {
    Config *config = config_new(TEST_RAW_LEN, TEST_COL_LEN);
    if(config == NULL)
        return 1;
    else
        return 0;
}

int test_new_matrix(void) {
    Config *config = config_new(TEST_RAW_LEN, TEST_COL_LEN);
    Matrix *matrix = matrix_new(config);
    if(matrix == NULL)
        return 1;
    else
        return 0;
}

int test_new_element(void) {
    Matrix *matrix = new_matrix();
    if(matrix == NULL)
        return 1;
    else
        return 0;
}

int test_matrix_add_element(void) {
    Matrix *matrix = new_matrix();
    if(matrix == NULL)
        return 1;
        
    Element *element = element_new(0,0,100);
    if(element == NULL)
        return 1;
    
    Status status = matrix_add(matrix, element);
    if(status == STAT_SUCCESS)
        return 0;
    else
        return 1;
}

static Matrix *new_matrix() {
    Config *config = config_new(TEST_RAW_LEN, TEST_COL_LEN);
    return matrix_new(config);
}