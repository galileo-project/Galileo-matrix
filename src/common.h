#ifndef MATRIX_COMMON_H_
#define MATRIX_COMMON_H_

const unsigned INI_MATRIX_COL = 32;
const unsigned INI_MATRIX_ROW = 32;

typedef short Status;
const Status STAT_SUCCESS        = 0;
const Status STAT_ERROR          = 1;
const Status STAT_ADD_ELE_ERR    = 10;
const Status STAT_ELE_EXIST_ERR  = 11;
const Status STAT_NEW_BLU_ERR    = 12;

typedef enum bool_e {
    False, True
} Bool;

void safe_free(void*);

#endif //MATRIX_COMMON_H_
