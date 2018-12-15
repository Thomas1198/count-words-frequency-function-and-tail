/**
* @date 16. 4. 2018
* @file htab_free.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

void htab_free(htab_t *t) {
    if (t != NULL) {
        htab_clear(t);
        free(t);
    }
}
