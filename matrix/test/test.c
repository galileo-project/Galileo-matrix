#include "common.h"
#include "matrix.h"
#include "element.h"

typedef void (*Func)(void);

int test_new_matrix(void);
int test_new_element(void);
int test_matrix_add_element(void);

int main() {
    Func functions[] = {test_new_matrix, 
                        test_new_element,
                        test_matrix_add_element};
    unsigned len = sizeof(functions)/sizeof(Func);
    
    for(int i = 0; i < len; i++) {
        int res = functions[i]();
        if(res != 0)
            return res;
        else
            continue;
    }
                                 
    return 0;
}

int test_new_matrix(void) {
    Matrix *matrix = matrix_new();
    if(matrix == NULL)
        return 1;
    else
        return 0
}

int test_new_element(void) {
    Matrix *matrix = matrix_new();
    if(matrix == NULL)
        return 1;
    else
        return 0
}

int test_matrix_add_element(void) {
    Matrix *matrix = matrix_new();
    if(matrix == NULL)
        return 1;
        
    Element *element = element_new(0,0,100);
    if(element == NULL)
        return 1;
    
    Status status matrix_add(matrix, element);
    if(status == STAT_SUCCESS)
        return 0;
    else
        return 1;
}