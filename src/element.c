#include "element.h"
#include <stdlib.h>

Element *element_new() {
    Element *element = (Element*)malloc(sizeof(Element));
    if(element == NULL)
        return NULL;
    else
        return element;
}

Blucket *blucket_new() {
    Blucket *blucket = (Blucket*)malloc(sizof(Blucket));
    if(blucket == NULL){
        return NULL;
    } else {
        blucket->len = 0;
        return blucket;
    }
        
}

Status blucket_add(Blucket *blucket, Element *element) {
    int target;
    if(element->row >= element->col)
        target = 0;
    else
        target = 1
    
    if(blucket->elements[target] != NULL){
        return STAT_ELE_EXIST_ERR;
    } else {
        blucket->elements[target] = blucket;
        return STAT_SUCCESS;
    }
}