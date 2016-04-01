#ifndef MATRIX_ELEMENT_H_
#define MATRIX_ELEMENT_H_

typedef struct element_s {
    unsigned col;
    unsigned raw;
    int value;
} Element;

typedef struct blucket_s {
    Element *(elements[2]);
    unsigned len;  
} Blucket;

//Element functions
Element *element_new(int);
Blucket *blucket_new();

#endif //MATRIX_ELEMENT_H_