#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }

  int count = 1;
  size_t res[n];

  for (int i = 0; i < n; i++) {
    res[i] = 0;
  }

  for (int i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      res[i] = count;
      count++;
    }
    else {
      res[i] = count;
      count = 1;
    }
  }

  if (array[n - 2] < array[n - 1]) {
    res[n - 1] = res[n - 2] + 1;
  }
  else {
    res[n - 1] = 1;
  }

  size_t max_num = res[0];
  for (int i = 1; i < n; i++) {
    if (res[i] > max_num) {
      max_num = res[i];
    }
  }
  return max_num;
}
