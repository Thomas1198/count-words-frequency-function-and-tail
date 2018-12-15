/**
* @date 16. 4. 2018
* @file htab_move.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

htab_t *htab_move(unsigned long new_size, htab_t *t2) {

    htab_t *new_table = htab_init(new_size);
    if (new_table == NULL || t2 == NULL)
        return NULL;

    new_table->arr_size = new_size;
    new_table->size = t2->size;

    unsigned long array_size_t2 = htab_bucket_count(t2);
    struct htab_listitem *pom = NULL;
    struct htab_listitem *tmp = NULL;

    //going through the array of pointers
    for (unsigned long i = 0; i < array_size_t2; i++) {
        //skip empty
        if (t2->htab_arr[i] == NULL)
            continue;

        tmp = t2->htab_arr[i];
        //going through the list
        while (tmp != NULL) {
            pom = htab_lookup_add(new_table, tmp->key);
            if (pom == NULL)
                return NULL;

            pom->data = tmp->data;
            tmp = tmp->next;
        }
    }
    htab_clear(t2);
    return new_table;

}
