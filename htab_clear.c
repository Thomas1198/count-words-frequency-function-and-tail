/**
* @date 16. 4. 2018
* @file htab_clear.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

void htab_clear(htab_t *t) {
    if (t == NULL)
        return;

    struct htab_listitem *tmp = NULL;
    struct htab_listitem *next = NULL;

    for (unsigned long i = 0; i < htab_size(t); i++) {
        if ((tmp = t->htab_arr[i]) == NULL)
            continue;
        while (tmp != NULL) {
            next = tmp->next;
            htab_remove(t, tmp->key);
            tmp = next;
        }
        t->htab_arr[i] = NULL;
    }
    t->size = 0;
}
