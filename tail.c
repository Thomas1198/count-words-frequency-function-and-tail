/**
* @date 16. 4. 2018
* @file tail.c
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFUALT_NUM_OF_LINES 10
#define MAX_LINE_LENGTH 1024
#define N_LINES_FILE argc == 4 && strcmp(argv[1], "-n") == 0 && atoi(argv[2]) >= 0
#define N_LINES_KEYBOARD argc == 3 && strcmp(argv[1], "-n") == 0 && atoi(argv[2]) >= 0

/*
 * @brief It will print last N lines of file or stdin
 * @param	n line from which start to print
 * @param file_name if NULL loads from stdin, else from the file
 * @return 1 when error, 0 success
*/
int tail(int n, char const *file_name) {
    FILE *fr;
    if (file_name != NULL) {
        fr = fopen(file_name, "r");
        if (fr == NULL) {
            fprintf(stderr, "Could not open the file\n");
            return 1;
        }
    } else
        fr = stdin;

    char buffer[n][MAX_LINE_LENGTH + 1];
    int c;
    int act_char = 0;
    int act_line = 0;
    int lines_num = 0;

    int number_of_shortened[n];
    int index = 0;

    while ((c = fgetc(fr)) != EOF) {
        buffer[act_line][act_char] = c;
        act_char++;

        if (c == '\n' || act_char == MAX_LINE_LENGTH) {
            if (act_char == MAX_LINE_LENGTH) {
                number_of_shortened[index++] = lines_num + 1;
                while (fgetc(fr) != '\n');
                buffer[act_line][act_char - 1] = '\n';   //pridani znaku noveho radku na konec orezaneho radku
            }
            act_char = 0;
            act_line++;
            lines_num++;
        }

        if (act_line == n)
            act_line = 0;
    }

    if (index > 0) {
        for (int i = 0; i < index; i++) {
            if (lines_num - n <
                number_of_shortened[i])   //staci nam informovat o ykraceni tech radku, co vypisujeme. Ostatni ne.
                fprintf(stderr, "Line number %d was over the length limit (%d). The line was shortened.\n",
                        number_of_shortened[i],
                        MAX_LINE_LENGTH);
        }
    }

    for (int i = (act_line == n || act_line >= lines_num) ? 0 : act_line, total = 0;
         total < lines_num && total < n; ++i, ++total) {
        for (int j = 0; j < MAX_LINE_LENGTH; ++j) {
            putchar(buffer[i][j]);
            if (buffer[i][j] == '\n')
                break;
        }
        if (i == n - 1)
            i = -1;
    }

    if (file_name != NULL && fclose(fr) == EOF) {
        fprintf(stderr, "Could not close the file\n");
        return 1;
    }

    return 0;
}


/*
 * @brief Process arguments and call tail function
 * @param	argc number of arguments
 * @param	argv arguments
*/
int main(int argc, char const **argv) {
    int status = 0;
    if (argc == 2) //tail file
        status = tail(DEFUALT_NUM_OF_LINES, argv[1]);
    else if (N_LINES_FILE) { //tail -n 20 file
        if (atoi(argv[2]) == 0) //if n == 0 nothing to print -> we are done
            return 0;
        status = tail(atoi(argv[2]), argv[3]);
    } else if (N_LINES_KEYBOARD) { //tail -n 20
        if (atoi(argv[2]) == 0) //if n == 0 nothing to print -> we are done
            return 0;

        status = tail(atoi(argv[2]), NULL);
    } else if (argc == 1) //tail
        status = tail(DEFUALT_NUM_OF_LINES, NULL);
    else { //error
        fprintf(stderr, "Arguments are not valid\n");
        status = 1;
    }

    if (status)
        return 1;

    return 0;
}
