#include "element.h"
#include <stdlib.h>

Element *element_new() {
    Element *element = (Element*)malloc(sizeof(Element));
    if(element == NULL)
        return NULL;
    else
        return element;
}

unsigned element_index(Element *element) {
    return element->col * element->row;
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

Status blucket_add(Blucket *blucket, Element *element, Bool update) {
    int target;
    if(element->row >= element->col)
        target = 0;
    else
        target = 1
    
    if(blucket->elements[target] != NULL && !update){
        return STAT_ELE_EXIST_ERR;
    } else {
        safe_free(blucket->elements[target]);
        blucket->elements[target] = element;
        return STAT_SUCCESS;
    }
}