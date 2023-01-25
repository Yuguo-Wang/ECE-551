#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "The input file number is incorrect.\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * category_words = read_category_word(argv[1]);
  replace_all_line_category(argv[2], category_words, false, true);
  free_catarray_t(category_words);
  return EXIT_SUCCESS;
}
