#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  bool used_permit;

  if (argc < 3 || argc > 4) {
    fprintf(stderr, "Less or too much argument");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    used_permit = false;
    catarray_t * category_words = read_category_word(argv[1]);
    replace_all_line_category(argv[2], category_words, used_permit, true);
    free_catarray_t(category_words);
  }

  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr, "Error: wrong format of selecting unused type");
      exit(EXIT_FAILURE);
    }

    used_permit = true;
    catarray_t * category_words = read_category_word(argv[2]);
    replace_all_line_category(argv[3], category_words, used_permit, true);
    free_catarray_t(category_words);
  }
  return EXIT_SUCCESS;
}
