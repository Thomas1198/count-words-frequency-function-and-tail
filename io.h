/**
* @date 16. 4. 2018
* @file io.h
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * @brief Gets next word from file
 * @param s pointer to array of chars to save the word
 * @param max maximal length of the word
 * @param f file with words
 * @return word or EOF
 */
int get_word(char *s, int max, FILE *f);
