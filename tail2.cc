/**
* @date 16. 4. 2018
* @file tail2.cc
* @author Tomas Dorda (xdorda00)
* GCC 6.4.0
*/

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <string.h>

/*
 * @brief It will print last N lines of file or stdin
 * calling the program with these arguments: ./name [-n number_of_lines] [file_name]  (order matters you can't call ./name -n number_of_lines file_name)
 * [-n number_of_lines] number of lines to print if not entered use default number
 * [file_name] if entered taking chars from the file, otherwise from stdin
 * @return 1 when error, 0 success
*/
int main (int argc, char **argv) {
  int number_of_lines = 10;
  char *file_name = NULL;
  char *endptr;
  char *number_of_lines_string = NULL;
  std::ifstream fr;
  std::string line;
  std::ios::sync_with_stdio(false); /* Making it faster */

  if( argc == 2 ) //tail file
    file_name = argv[1];
  else if (argc == 4 && strcmp(argv[1], "-n") == 0) { //tail -n 20 <file
    file_name = argv[3];
    number_of_lines_string = argv[2];
    }
  else if (argc == 3 && strcmp(argv[1], "-n") == 0) //tail -n 20
    number_of_lines_string = argv[2];
  else if( argc == 1 ) //tail
  {
      std::cerr << "Invalid arguments" << std::endl;
      file_name = NULL;
  }
  else { //error
    return 1;
  }

  if (file_name != NULL) {
    fr.open(file_name);
    if (!fr.is_open()) {
      std::cerr << "Couldn't open the file" << std::endl;
      exit(1);
    }
  }
  else
    fr.std::basic_ios<char>::rdbuf(std::cin.rdbuf());

  if (number_of_lines_string != NULL) {
    number_of_lines = strtol(number_of_lines_string, &endptr, 10);

    if (endptr[0] != '\0' || number_of_lines < 0 ) {
      std::cerr << "Number of lines is not valid" << std::endl;
      exit(1);
    }
    if (number_of_lines == 0)
      return 0;
  }

  std::queue<std::string> que;
  int i = 0;

  while (std::getline(fr, line)) {
    que.push(line);
    i++;

    if (i > number_of_lines)
      que.pop();
  }
  fr.close();

  while (!que.empty()) {
    std::cout << que.front() << std::endl;
    que.pop();
  }

  return 0;
}
