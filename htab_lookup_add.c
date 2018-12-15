/**
* @date 16. 4. 2018
* @file htab_lookup_add.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

struct htab_listitem *htab_lookup_add(htab_t *t, const char *key) {
    if (t == NULL || key == NULL)
        return NULL;

    struct htab_listitem *item = htab_find(t, key);
    if (item != NULL) { //item found
        item->data++;
        return item;
    }

    //allocating new item
    item = (struct htab_listitem *) malloc(sizeof(struct htab_listitem));
    if (item == NULL)
        return NULL;

    //allocating the key
    item->key = (char *) malloc(sizeof(char) * (strlen(key) + 1));

    if (item->key == NULL) {
        free(item);
        return NULL;
    }

    //init
    strcpy(item->key, key);
    item->data = 1;
    item->next = NULL;

    //inserting
    unsigned int index = htab_hash_function(key) % htab_size(t);

    struct htab_listitem *tmp = t->htab_arr[index];
    if (tmp == NULL) {
        t->htab_arr[index] = item;
        t->size++;
        return item;
    }

    while (tmp != NULL) {
        if (tmp->next == NULL) {
            tmp->next = item;
            t->size++;
            return item;
        }
        tmp = tmp->next;
    }
    return item;
}
