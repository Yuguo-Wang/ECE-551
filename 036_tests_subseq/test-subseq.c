#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test(int * array, size_t n, size_t res) {
  if (res != maxSeq(array, n)) {
    printf("GG");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int arr_0[1] = {0};
  int arr_1[2] = {2, 3};
  int arr_2[7] = {2, 2, 4, 9, 8, 2, 2};
  int arr_3[5] = {0, 0, 0, 0, 0};
  int arr_4[5] = {-2, -1, 1, 3, -1};
  int * arr_5 = NULL;
  // int arr_6[] = {2, 2, 4, 4, 5, 6, 6};

  test(arr_0, 1, 1);
  test(arr_1, 2, 2);
  test(arr_2, 7, 3);
  test(arr_3, 5, 1);
  test(arr_4, 5, 4);
  test(arr_5, 0, 0);
  // test(arr_6, 7, 3);
  exit(EXIT_SUCCESS);
}
