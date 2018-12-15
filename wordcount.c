/**
* @date 16. 4. 2018
* @file wordcount.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "htab.h"
#include "io.h"

#ifndef MAX_LENGHT
#define MAX_LENGHT 128
#define TABLE_SIZE 3079
#endif

void print_item(const char *key, unsigned long data) {
    printf("%-15s\t\t%-10ld\n", key, data);
}

int main() {
    htab_t *table = htab_init(TABLE_SIZE);
    if (table == NULL) {
        fprintf(stderr, "Allocation error.\n");
        return 1;
    }

    char *word = (char *) malloc(sizeof(char) * MAX_LENGHT);
    for (int i = 0; i < MAX_LENGHT ; ++i) {
        word[i] = '\0';
    }

    if (word == NULL) {
        fprintf(stderr, "Allocation error\n");
        free(table);
        return 1;
    }


    int ret_value = 1;
    puts("Start entering any words or numbers and when you are done type EOF character (linux: hit \"ENTER\" and then \"CTRL\" + \"Z\")");
    do {
        ret_value = get_word(word, MAX_LENGHT, stdin);
        if (ret_value != EOF && htab_lookup_add(table, word) == NULL) {
            fprintf(stderr, "Allocation error\n");
            htab_free(table);
            free(word);
            return 1;
        }
    } while (ret_value != EOF);

    putchar('\n');
    htab_foreach(table, print_item);
    htab_free(table);
    free(word);

    return 0;
}
