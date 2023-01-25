#include <assert.h>

#include <cmath>
#include <cstdlib>
#include <ostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class xy : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int max_invoke;
  if (high > low) {
    max_invoke = log2(high - low) + 1;
  }
  else {
    max_invoke = 1;
  }
  CountedIntFn * wrap_count = new CountedIntFn(max_invoke, f, mesg);
  int res = binarySearchForZero(wrap_count, low, high);
  assert(res == expected_ans);
}

int main(void) {
  xy * xy1 = new xy();
  check(xy1, -1, 4, 0, "normal\n");
  check(xy1, 1, 6, 1, "Positive\n");
  check(xy1, -5, -2, -3, "Negative\n");
  check(xy1, 0, 2, 0, "zero inclusively");
  check(xy1, -2, 0, -1, "zero exclusively");
  delete xy1;
  return EXIT_SUCCESS;
}
