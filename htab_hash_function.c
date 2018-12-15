/**
* @date 16. 4. 2018
* @file htab_hash_function.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"

unsigned int htab_hash_function(const char *str) {
    unsigned int h = 0;     // 32bit
    const unsigned char *p;
    for (p = (const unsigned char *) str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}
