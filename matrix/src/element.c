#include "element.h"
#include <stdlib.h>

//element functions 
Element *element_new(unsigned raw, unsigned col, int value) {
    Element *element = (Element*)malloc(sizeof(Element));
    if(element == NULL)
        return NULL;
    
    element->raw   = raw;
    element->col   = col;
    element->value = value;
    
    return element;
}

unsigned element_index(Element *element) {
    return element->col * element->raw;
}

Element *element_seek_by_pos(Element *element, unsigned raw, unsigned col) {
    if(element->raw == raw && element->col == col)
        return element;
    else if(element->next == NULL)
        return NULL;
    else
        return element_seek_by_pos(element->next, raw, col);
}

Element *element_seek_by_val(Element *element, int value) {
    if(element == NULL)
        return NULL;
        
    if(element->value == value)
        return element;
    else if(element->next == NULL)
        return NULL;
    else
        return element_seek_by_val(element->next, value);
}

//blucket functions 
Blucket *blucket_new() {
    Blucket *blucket = (Blucket*)malloc(sizeof(Blucket));
    if(blucket == NULL) {
        return NULL;
    } else {
        blucket->len = 0;
        return blucket;
    }
        
}

Status blucket_add(Blucket *blucket, Element *element, Bool update) {
    Element *tmp = blucket->elements; 
    if(tmp == NULL) {
        element->pre = NULL;
        blucket->elements = element;
        return STAT_SUCCESS;
    } else if(POS_EQ(tmp, element) && update) {
        element->pre = NULL;
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
    
    return STAT_SUCCESS;
}

Status blucket_free(Blucket* blucket) {
    Element *element;
    
    element = blucket->elements;
    if(element == NULL)
        return STAT_SUCCESS;
        
    while(element->next != NULL)
        element = element->next;
    
    while(element->pre != NULL) {
        safe_free(element->next);
        element = element->pre;
    }
    safe_free(element);
    
    return STAT_SUCCESS;
}