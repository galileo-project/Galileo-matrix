#include "element.h"
#include <stdlib.h>

Element *element_new() {
    Element *element = (Element*)malloc(sizeof(Element));
    if(element == NULL)
        return NULL;
    else
        return element;
}