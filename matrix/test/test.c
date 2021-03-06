#include <stdio.h>
#include "common.h"
#include "matrix.h"
#include "utils.h"
#include "element.h"

#define LOG_ERR(msg) do{\
        printf("ERROR:   %s.\n", msg);\
    }while(0)
    
#define LOG_SUCCESS(msg) do{\
        printf("SUCCESS: %s.\n", msg);\
    }while(0)
    
#define LOG_INFO(msg) do{\
        printf("INFO:    %s.\n", msg);\
    }while(0)
    
#define LOG_RAW(msg) do{\
        printf("%s.\n", msg);\
    }while(0)

const unsigned TEST_RAW_LEN = 100;
const unsigned TEST_COL_LEN = 100;

typedef int (*Func)(void);

static Matrix *new_matrix(void);
static int fill_matrix(Matrix*, unsigned, unsigned);
int test_new_matrix(void);
int test_new_element(void);
int test_matrix_add_element(void);
int test_config_new(void);
int test_matrix_find_element(void);
int test_matrix_clear(void);
int test_matrix_update(void);
int test_matrix_print(void);

int main() {
    Func functions[] = {&test_config_new,
                        &test_new_matrix, 
                        &test_new_element,
                        &test_matrix_add_element,
                        &test_matrix_find_element,
                        &test_matrix_clear,
                        &test_matrix_update,
                        &test_matrix_print};
    unsigned len = sizeof(functions)/sizeof(functions[0]);
    int result = 0;

    for(int i = 0; i < len; i++) {
        if((*functions[i])() != 0)
            result = 1;
    }
    
    if(result == 0)
        LOG_RAW("success");
    else
        LOG_RAW("failed");
       
    return result;
}

//////// test functions //////////

int test_config_new(void) {
    Config *config = config_new(TEST_RAW_LEN, TEST_COL_LEN);
    if(config == NULL) {
        LOG_ERR("new config");
        return 1;
    } else {
        LOG_SUCCESS("new config");
        return 0;
    }
}

int test_new_matrix(void) {
    Config *config = config_new(TEST_RAW_LEN, TEST_COL_LEN);
    Matrix *matrix = matrix_new(config);
    if(matrix == NULL) {
        LOG_ERR("new matrix");
        return 1;
    }
    
    safe_free(config);
    safe_free(matrix);
    LOG_SUCCESS("new matrix");
    return 0;
}

int test_new_element(void) {
    Element *element = element_new(0,0,100);
    if(element == NULL) {
        LOG_ERR("new element");
        return 1;
    }

    safe_free(element);
    LOG_SUCCESS("new element");
    return 0;
        
}

int test_matrix_add_element(void) {
    Matrix *matrix = new_matrix();
    if(matrix == NULL) {
        LOG_ERR("add element to matrix -> new matrix");
        return 1;
    }
        
    Element *element = element_new(0,0,100);
    if(element == NULL) {
        safe_free(matrix);
        LOG_ERR("add element to matrix -> new element");
        return 1;
    }
    
    Status status = matrix_add(matrix, element);
    if(status != STAT_SUCCESS) {
        safe_free(matrix);
        safe_free(element);
        LOG_ERR("add element to matrix");
        return 1;    
    }
    
    safe_free(element);
    safe_free(matrix);
    LOG_SUCCESS("add element to matrix");
    return 0;
}

int test_matrix_find_element(void) {
    Element *element_by_pos;
    Element *element_by_val;
    Matrix *matrix = new_matrix();
    int res = fill_matrix(matrix, 20, 20);
    if(res != 0) {
        LOG_ERR("test matrix find element -> fill matrix error");
        return res;
    }
    
    //find element by pos
    element_by_pos = matrix_find_by_pos(matrix, 3, 15);
    if(element_by_pos == NULL) {
        LOG_ERR("find element from matrix by pos");
        return 1;
    }
    if(element_by_pos->value == 3*15) {
        LOG_SUCCESS("find element from matrix by pos");
    } else {
        LOG_ERR("find element from matrix by pos");
        return 1;
    }
    
    //find element by value
    element_by_val = matrix_find_by_val(matrix, 3*15);
    if(element_by_val == NULL) {
        LOG_ERR("find element from matrix by value");
        return 1;
    }
    while(element_by_val != NULL) {
        if(element_by_val->row == 3 && element_by_val->col == 15) {
            LOG_SUCCESS("find element from matrix by value");
            break;
        } else if(element_by_val->next == NULL){
            LOG_ERR("find element from matrix by value");
            return 1;
        } else {
            element_by_val = element_by_val->next;
        }
    }
    
    return 0;
}

int test_matrix_clear(void) {
    Matrix *matrix = new_matrix();
    int res = fill_matrix(matrix, 20, 20);
    if(res != 0) {
        LOG_ERR("test matrix clear -> fill matrix error");
        return res;
    }
    
    Status status = matrix_clear(matrix);
    if(status != STAT_SUCCESS) {
        LOG_ERR("test matrix clear");
        return 1;
    } else {
        LOG_SUCCESS("test matrix clear");
        return 0;
    }
    
}

int test_matrix_update(void) {
    Matrix *matrix = new_matrix();
    int res = fill_matrix(matrix, 20, 20);
    if(res != 0) {
        LOG_ERR("test matrix update -> fill matrix error");
        return res;
    }
    
    Element *new_element = element_new(10, 10, 10+10);
    Status status = matrix_update(matrix, new_element);
    if(status != STAT_SUCCESS) {
        LOG_ERR("test matrix update");
        return 1;
    } else {
        Element *element = matrix_find_by_pos(matrix, 10, 10);
        if(element == NULL) {
            LOG_ERR("test matrix update -> find element error");
            return 1;
        } else {
            if(new_element->value == element->value) {
                LOG_SUCCESS("test matrix update");
                return 0;
            } else {
                LOG_ERR("test matrix update, can't update");
                return 1;
            }
        }
    }
        
}

int test_matrix_print(void) {
    Matrix *matrix = new_matrix();
    int res = fill_matrix(matrix, 20, 20);
    if(res != 0) {
        LOG_ERR("test matrix print -> fill matrix error");
        return res;
    }
    
    matrix_print(matrix);
    LOG_SUCCESS("matrix print");
    return 0;
}

//////// test functions end //////////

static Matrix *new_matrix(void) {
    Config *config = config_new(TEST_RAW_LEN, TEST_COL_LEN);
    return matrix_new(config);
}

static int fill_matrix(Matrix *matrix, unsigned row, unsigned col) {
    for(unsigned i =0; i <= row; i++) {
        for(unsigned j = 0; j <= col; j++) {
            Element *element = element_new(i, j, i*j);
            if(element == NULL)
                return 1;
                
            Status status = matrix_add(matrix, element);
            if(status != STAT_SUCCESS)
                return 1;
        }
    }
    
    return 0;
}
