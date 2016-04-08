#ifndef MATRIX_COMMON_H_
#define MATRIX_COMMON_H_

//marco
#define POS_EQ(ele_l, ele_r) (\
                                 (ele_l == NULL || ele_r == NULL) ? 0 : \
                                 (\
                                     ((ele_l)->row == (ele_r)->row && (ele_l)->col == (ele_r)->col) ? 1 : 0 \
                                 )\
                             )
                             
typedef short Status;
extern const Status STAT_SUCCESS, 
                    STAT_ERROR, 
                    STAT_ADD_ELE_ERR, 
                    STAT_ELE_EXIST_ERR, 
                    STAT_NEW_BLU_ERR, 
                    STAT_INIT_MATRIX_ERR, 
                    STAT_MAX_MATRIX_LEN_ERR;

typedef enum bool_e {
    False = 0, 
    True  = 1
} Bool;

void safe_free(void*);

#endif //MATRIX_COMMON_H_
