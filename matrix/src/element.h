#include "common.h"

#ifndef MATRIX_ELEMENT_H_
#define MATRIX_ELEMENT_H_

typedef struct element_s {
    unsigned col;
    unsigned row;
    int      value;
    struct element_s *next;
    struct element_s *pre;
} Element;

typedef struct blucket_s {
    Element *elements;
    unsigned len;
} Blucket;

//Element functions
Element *element_new(unsigned, unsigned, int);
Element* element_next(Element*);
Element *element_copy(Element*);
Element *element_link(Element*, Element*);
void     element_print(Element*);

Blucket *blucket_new();
Status blucket_add(Blucket*, Element*, Bool);
Status blucket_free(Blucket*);
Element *blucket_seek_by_pos(Blucket*, unsigned, unsigned);
Element *blucket_seek_by_val(Blucket*, int);

#endif //MATRIX_ELEMENT_H_
