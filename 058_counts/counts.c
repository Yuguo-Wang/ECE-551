#include "counts.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * res = malloc(sizeof(*res));
  if (res == NULL) {
    return res;
  }
  res->array = NULL;
  res->counts = 0;
  res->unknown_names = 0;
  return res;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown_names++;
  }

  else {
    bool found = false;
    for (size_t i = 0; i < c->counts; i++) {
      if (strcmp(c->array[i]->string, name) == 0) {
        c->array[i]->num_string++;
        found = true;
      }
    }
    if (!found) {
      c->array = realloc(c->array, sizeof(*c->array) * (c->counts + 1));
      one_count_t * data = malloc(sizeof(*data));

      c->array[c->counts] = data;
      c->array[c->counts]->string = name;
      c->array[c->counts]->num_string = 1;

      c->counts++;
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->counts; i++) {
    fprintf(outFile, "%s:%ld\n", c->array[i]->string, c->array[i]->num_string);
  }
  if (c->unknown_names > 0) {
    fprintf(outFile, "<unknown>:%ld\n", c->unknown_names);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->counts; i++) {
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
