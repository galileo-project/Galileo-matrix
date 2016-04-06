#ifndef MATRIX_ELEMENT_H_
#define MATRIX_ELEMENT_H_

#include "common.h"

typedef struct element_s {
    unsigned col;
    unsigned raw;
    int value;
    struct element_s *next;
    struct element_s *pre;
} Element;

typedef struct blucket_s {
    Element *elements;
    unsigned len;
} Blucket;

//Element functions
Element *element_new(int);
unsigned element_index(Element*);
Element *element_seek_by_pos(Blucket*, unsigned, unsigned);
Element *element_seek_by_val(Blucket*, int);

Blucket *blucket_new();
Status blucket_add(Blucket*, Element*, Bool);
Status blucket_free(Blucket*);

#endif //MATRIX_ELEMENT_H_
