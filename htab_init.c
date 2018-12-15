/**
* @date 16. 4. 2018
* @file htab_init.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

htab_t *htab_init(size_t size) {
    if (size <= 0)
        return NULL;

    htab_t *t = (htab_t *) malloc(sizeof(htab_t) + size * sizeof(struct htab_listitem *));
    if (t == NULL)
        return NULL;

    t->size = 0;
    t->arr_size = size;

    for (unsigned long i = 0; i < size; i++)
        t->htab_arr[i] = NULL;
    return t;
}
