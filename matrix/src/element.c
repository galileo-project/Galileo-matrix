#include "element.h"
#include <stdlib.h>

//element functions 
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

Element *element_seek_by_pos(Element *element, unsigned row, unsigned col) {
    if(element->row == row && element->col == col)
        return element;
    else if(element->next == NULL)
        return NULL;
    else
        return element_seek_by_pos(element->next, row, col);
}

Element *element_seek_by_val(Element *element, int value) {
    if(element->value == value)
        return element;
    else if(element->next == NULL)
        return NULL;
    else
        return element_seek_by_val(element->next, value);
}

//blucket functions 
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
    Element *tmp = blucket->elements; 
    if(tmp == NULL) {
        element->pre = blucket->elements;
        blucket->elements = element;
        return STAT_SUCCESS;
    } else if(POS_EQ(tmp, element) && update) {
        element->pre = blucket->elements;
        element->next = blucket->elements->next;
        blucket->elements = element;
        return STAT_SUCCESS;
    }
        
    while(tmp != NULL) {
        if(POS_EQ(tmp->next, element) && update) {
            element->pre = tmp->next->pre;
            element->pre = tmp->next->next;
            safe_free(tmp->next);
            tmp->next = element;
            return STAT_SUCCESS;
        } else if(tmp->next == NULL) {
            element->pre = tmp;
            tmp->next = element;
            return STAT_SUCCESS;
        } else {
            tmp = tmp->next;
            continue;
        }
    }
}
