#ifndef MATRIX_ELEMENT_H_
#define MATRIX_ELEMENT_H_

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
Blucket *blucket_new();
Status blucket_add(Element*, Bool);

#endif //MATRIX_ELEMENT_H_