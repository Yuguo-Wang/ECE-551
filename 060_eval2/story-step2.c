#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input argument");
    exit(EXIT_FAILURE);
  }
  catarray_t * category_words = read_category_word(argv[1]);
  printWords(category_words);
  free_catarray_t(category_words);
  return EXIT_SUCCESS;
}
