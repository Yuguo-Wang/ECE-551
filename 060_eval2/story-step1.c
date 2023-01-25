#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input argument");
    exit(EXIT_FAILURE);
  }
  replace_all_line_category(argv[1], NULL, false, false);
  return EXIT_SUCCESS;
}
