#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matrix[10][10];

void rotateMatrix(FILE * f) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      int each_char = fgetc(f);
      if (each_char == EOF || each_char == '\n') {
        fprintf(stderr, "Failed for short line");
        exit(EXIT_FAILURE);
      }
      matrix[j][9 - i] = each_char;
    }

    if (fgetc(f) != '\n') {
      fprintf(stderr, "Failed for long line");
      exit(EXIT_FAILURE);
    }
  }
  if (fgetc(f) != EOF) {
    fprintf(stderr, "Failed for more than 10 lines");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid input");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open the file");
    return EXIT_FAILURE;
  }

  rotateMatrix(f);
  if (fclose(f) == 0) {
    fprintf(stderr, "Successfully close the file");
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        printf("%c", matrix[i][j]);
      }
      printf("\n");
    }
    return EXIT_SUCCESS;
  }
  else {
    fprintf(stderr, "Failed to close the file");
    return EXIT_FAILURE;
  }
}
