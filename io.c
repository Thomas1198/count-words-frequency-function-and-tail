/**
* @date 16. 4. 2018
* @file io.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include "io.h"

int get_word(char *s, int max, FILE *f) {
    if (s == NULL || f == NULL || max <= 0)
        return EOF;

    int c;

    while ((c = fgetc(f)) != EOF && !isalnum(c));

    if (c == EOF)
        return EOF;

    if (isalnum(c))
        s[0] = c;

    int i = 1;

    while ((c = fgetc(f)) != EOF && i < max - 1) {
        if (!isalnum(c)) {
            s[i] = '\0';
            break;
        }

        s[i] = (char) c;
        i++;
    }

    if (i == max - 1) {
        s[i] = '\0';
        fprintf(stderr, "Word was too long, thus it was shortened\n");
        while (isalnum(c = fgetc(f)));  //throwing the rest of the word away
    }


    ungetc(c, f);

    return i;
}
