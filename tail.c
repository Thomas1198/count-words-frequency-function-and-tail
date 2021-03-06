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
 * @param n line from which start to print
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

    if(n<0){
        fprintf(stderr, "Invalid parameter n (n has to be greater or equal to 0)\n");
        return 1;
    }

    int c;
    if((c = fgetc(fr)) == EOF)
        return 0;
    else
        ungetc(c,fr);
    char buffer[n][MAX_LINE_LENGTH + 1];
    int act_char_num = 0;
    int act_line = 0;
    int lines_num = 0;

    int number_of_shortened[n];
    int index = 0;

    while (1) {
        c = fgetc(fr);
        buffer[act_line][act_char_num] = c;
        act_char_num++;

        if (c == '\n' || act_char_num == MAX_LINE_LENGTH || c == EOF) {
            if (act_char_num == MAX_LINE_LENGTH) {
                number_of_shortened[index++] = lines_num + 1;
                while (fgetc(fr) != '\n');
                buffer[act_line][act_char_num - 1] = '\n';
            }
            act_char_num = 0;
            act_line++;
            lines_num++;
            if (c == EOF) break;
        }

        if (act_line == n)
            act_line = 0;
    }

    if (index > 0) {
        for (int i = 0; i < index; i++) {
            if (lines_num - n <
                number_of_shortened[i])   //we will notify only about printed lines
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
    int ret_value = 0;

    if (argc == 2) //tail file
        ret_value = tail(DEFUALT_NUM_OF_LINES, argv[1]);
    else if (N_LINES_FILE) { //tail -n 20 file
        if (atoi(argv[2]) == 0) //if n == 0 nothing to print -> we are done
            return 0;
        ret_value = tail(atoi(argv[2]), argv[3]);
    } else if (N_LINES_KEYBOARD) { //tail -n 20
        if (atoi(argv[2]) == 0) //if n == 0 nothing to print -> we are done
            return 0;

        ret_value = tail(atoi(argv[2]), NULL);
    } else if (argc == 1) //tail
        ret_value = tail(DEFUALT_NUM_OF_LINES, NULL);
    else { //error
        fprintf(stderr, "Arguments are not valid\n");
        ret_value = 1;
    }

    if (ret_value)
        return 1;

    return 0;
}
