#include "element.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//element functions 
Element *element_new(unsigned row, unsigned col, int value) {
    Element *element = (Element*)malloc(sizeof(Element));
    if(element == NULL)
        return NULL;
    
    element->row   = row;
    element->col   = col;
    element->value = value;
    element->pre   = NULL;
    element->next  = NULL;
    
    return element;
}

void element_print(Element *element) {
    if(element == NULL)
        printf("(%s, %s): %4s\n", "null", "null", "null");
    else
        printf("(%d, %d): %4d\n", element->row, element->col, element->value);
}

Element* element_next(Element *element) {
    if(element == NULL)
        return NULL;
    else
        return element->next;
}

Element *element_copy(Element *target) {
    return element_new(target->row, target->col, target->value);
}

Element *element_link(Element* header, Element *element) {
    Element *tmp = element_copy(element);
    if(tmp == NULL)
        return NULL;
    
    if(header != NULL) {
        tmp->next   = header;
        header->pre = tmp;
    }
    
    return tmp;
}

//blucket functions 
Blucket *blucket_new() {
    Blucket *blucket = (Blucket*)malloc(sizeof(Blucket));
    if(blucket == NULL) {
        return NULL;
    } else {
        blucket->len = 0;
        blucket->elements = NULL;
        return blucket;
    }
        
}

Status blucket_add(Blucket *blucket, Element *element, Bool update) {
    Element *tmp = blucket->elements; 
    if(tmp == NULL) {
        blucket->elements = element;
        blucket->len++;
        return STAT_SUCCESS;
    }
    
    while(tmp != NULL) {
        if(POS_EQ(tmp, element) && update) {
            element->pre = tmp->pre;
            element->next = tmp->next;
            if(blucket->elements == tmp)
                blucket->elements = element;
            if(element->pre != NULL)
                element->pre->next = element;
                
            safe_free(tmp);
            return STAT_SUCCESS;
        } else if(tmp->next == NULL) {
            element->pre = tmp;
            tmp->next = element;
            blucket->len++;
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

Element *blucket_seek_by_pos(Blucket *blucket, unsigned row, unsigned col) {
    Element *element = blucket->elements;
    if(element == NULL)
        return NULL;
                
    while(element != NULL) {
        if(element->row == row && element->col == col)
            return element;
        else if(element->next == NULL)
            return NULL;
        else
            element = element->next;
    }
    
    return NULL;
}

Element *blucket_seek_by_val(Blucket *blucket, int value) {
    Element *element = blucket->elements;
    Element *ret = NULL;
    
    if(element == NULL)
        return NULL;
        
    while(element != NULL) {
        if(element->value == value) {
            ret = element_link(ret, element);
        } else if(element->next == NULL) { 
            break;
        }
        
        element = element->next;
    }
    
    return ret;
}