/**
* @date 16. 4. 2018
* @file htab_remove.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

bool htab_remove(htab_t *t, const char *key) {

    if (t == NULL || key == NULL)
        return false;

    unsigned int index = htab_hash_function(key) % htab_bucket_count(t);

    struct htab_listitem *actual = t->htab_arr[index];
    struct htab_listitem *previous = NULL;

    while (actual != NULL) {
        if (strcmp(actual->key, key) == 0)
            break;
        previous = actual;
        actual = actual->next;
    }

    if (actual == NULL)
        return false;

    free(actual->key);
    t->size--;

    if (actual->next != NULL) {
        if (previous != NULL) {
            previous->next = actual->next;
        } else {
            t->htab_arr[index] = actual->next;
        }
    } else {
        if (previous != NULL) {
            previous->next = NULL;
        } else {
            t->htab_arr[index] = NULL;
        }
    }

    free(actual);
    return true;
}
