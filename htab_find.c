/**
* @date 16. 4. 2018
* @file htab_find.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

struct htab_listitem *htab_find(htab_t *t, const char *key) {
    if (t == NULL)
        return NULL;

    unsigned int index = (htab_hash_function(key) % htab_bucket_count(t));

    for (struct htab_listitem *tmp = t->htab_arr[index]; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->key, key) == 0)
            return tmp;
    }

    return NULL;
}
