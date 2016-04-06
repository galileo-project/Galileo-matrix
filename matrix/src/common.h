#ifndef MATRIX_COMMON_H_
#define MATRIX_COMMON_H_

#include "element.h"
#include "matrix.h"

const unsigned INI_MATRIX_COL = 32;
const unsigned INI_MATRIX_ROW = 32;

typedef short Status;
const Status STAT_SUCCESS         = 0;
const Status STAT_ERROR           = 1;
const Status STAT_ADD_ELE_ERR     = 10;
const Status STAT_ELE_EXIST_ERR   = 11;
const Status STAT_NEW_BLU_ERR     = 12;
const Status STAT_INIT_MATRIX_ERR = 13;

typedef enum bool_e {
    False, True
} Bool;

void safe_free(void*);
unsigned hash_generator(Element*, Matrix*);


//marco
#define POS_EQ(ele_l, ele_r) (\
                                 (ele_l == NULL || ele_r == NULL) ? 0 : \
                                 (\
                                     ((ele_l)->row == (ele_r)->row && (ele_l)->col == (ele_r)->col) ? 1 : 0 \
                                 )\
                             )

#endif //MATRIX_COMMON_H_
