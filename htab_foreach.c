/**
* @date 16. 4. 2018
* @file htab_foreach.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

void htab_foreach(htab_t *t, void (*function)(const char *, unsigned long)) {
    if (t == NULL || function == NULL)
        return;

    unsigned long size_of_array = htab_bucket_count(t);

    for (unsigned long i = 0; i < size_of_array; i++) {
        for (struct htab_listitem *tmp = t->htab_arr[i]; tmp != NULL; tmp = tmp->next) {
            function(tmp->key, tmp->data);
        }
    }
}
