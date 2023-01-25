#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int max_index(int * array) {
  int index = 0;
  int maxnum = array[0];
  for (int i = 1; i < 26; i++) {
    if (array[i] > maxnum) {
      maxnum = array[i];
      index = i;
    }
  }
  return index;
}

void frequency(FILE * f) {
  int nums[26];
  for (int i = 0; i < 26; i++) {
    nums[i] = 0;
  }
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      nums[c]++;
    }
    //printf("%c", c);
  }

  int max_i = max_index(nums);
  int key = max_i >= 4 ? max_i - 4 : 26 + max_i - 4;
  printf("%d\n", key);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  // int key = atoi(argv[1]);
  //if (key == 0) {
  //fprintf(stderr,"Invalid key (%s): must be a non-zero integer\n", argv[1]);
  //return EXIT_FAILURE;
  //}
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  frequency(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
