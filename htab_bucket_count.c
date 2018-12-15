/*
htab_bucket_count.c
Reseni IJC-DU2, priklad 2, 16. 4. 2018
Preklad: GCC 6.4.0
Autor: Tomas Dorda, FIT
*/

#include "htab.h"

unsigned long htab_bucket_count(htab_t *t)
{
    return t->arr_size;
}
