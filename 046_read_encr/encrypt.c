#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void encrypt(FILE * f, int key) {  //input.txt, 5
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);  //a, n
      c -= 'a';
      c += key;
      c %= 26;
      c += 'a';  // f, s
    }
    printf("%c", c);
  }
}

int main(int argc, char ** argv) {
  if (argc != 3) {  // len('.encrypt.c 5 input.txt') = 3
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  int key = atoi(argv[1]);  // char -> int
  if (key == 0) {
    fprintf(stderr, "Invalid key (%s): must be a non-zero integer\n", argv[1]);
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[2], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  encrypt(f, key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
