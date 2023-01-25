#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME

  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Failed to open the file\n");
    return NULL;
  }

  kvarray_t * kv_arr = malloc(sizeof(*kv_arr));

  kv_arr->pair_arr = malloc(sizeof(*kv_arr->pair_arr));
  kv_arr->pair_num = 0;

  //store one line from file
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) >= 0) {
    kv_arr->pair_num++;
    kv_arr->pair_arr =
        realloc(kv_arr->pair_arr, sizeof(*kv_arr->pair_arr) * kv_arr->pair_num);

    kv_arr->pair_arr[kv_arr->pair_num - 1] =
        malloc(sizeof(*kv_arr->pair_arr[kv_arr->pair_num - 1]));

    char * ptr = strchr(line, '=');
    kv_arr->pair_arr[kv_arr->pair_num - 1]->key = strndup(line, ptr - line);
    char * end = strchr(line, '\n');
    kv_arr->pair_arr[kv_arr->pair_num - 1]->value = strndup(ptr + 1, end - ptr - 1);
  }
  fclose(f);
  free(line);
  return kv_arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->pair_num; i++) {
    free(pairs->pair_arr[i]->key);
    free(pairs->pair_arr[i]->value);

    free(pairs->pair_arr[i]);
  }
  free(pairs->pair_arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->pair_num; i++) {
    printf(
        "key = '%s' value = '%s'\n", pairs->pair_arr[i]->key, pairs->pair_arr[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->pair_num; i++) {
    if (strcmp(key, pairs->pair_arr[i]->key) == 0) {
      return pairs->pair_arr[i]->value;
    }
  }
  return NULL;
}
