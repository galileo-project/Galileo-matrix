#include <stdio.h>
#include "common.h"
#include "matrix.h"
#include "element.h"

#define LOG_ERR(msg) do{\
        printf("ERROR: %s .\n", msg);\
    }while(0)
#define LOG_SUCCESS(msg) do{\
        printf("SUCCESS: %s .\n", msg);\
    }while(0)

const unsigned TEST_RAW_LEN = 100;
const unsigned TEST_COL_LEN = 100;

typedef int (*Func)(void);

static Matrix *new_matrix(void);
int test_new_matrix(void);
int test_new_element(void);
int test_matrix_add_element(void);
int test_config_new(void);

int main() {
    Func functions[] = {&test_config_new,
                        &test_new_matrix, 
                        &test_new_element,
                        &test_matrix_add_element};
    unsigned len = sizeof(functions)/sizeof(functions[0]);

    for(int i = 0; i < len; i++) {
        int res = (*functions[i])();
        if(res != 0)
            return res;
        else
            continue;
    }
    
    LOG_SUCCESS("all mod test sucess.");
    return 0;
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

//////// test functions end //////////

static Matrix *new_matrix(void) {
    Config *config = config_new(TEST_RAW_LEN, TEST_COL_LEN);
    return matrix_new(config);
}