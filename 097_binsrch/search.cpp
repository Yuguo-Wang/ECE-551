#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low > high) {
    exit(EXIT_FAILURE);
  }

  if (low == high - 1 || low == high) {
    return low;
  }

  int mid = (high - low) / 2 + low;
  int res = f->invoke(mid);

  if (res == 0) {
    return mid;
  }

  else if (res > 0) {
    return binarySearchForZero(f, low, mid);
  }

  else {
    return binarySearchForZero(f, mid, high);
  }
  return low;
}
