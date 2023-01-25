#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  unsigned length = strlen(inputName) + strlen(suffix) + 1;

  char * res = malloc(length * sizeof(*res));
  //return res;
  strcpy(res, inputName);
  strcat(res, suffix);
  return res;
}
