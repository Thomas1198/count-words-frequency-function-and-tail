/**
* @date 16. 4. 2018
* @file htab_size.h
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

size_t htab_size(htab_t *t) {
    return t->arr_size;
}
