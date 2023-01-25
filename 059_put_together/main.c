#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME

  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Cannot open the file\n");
    return NULL;
  }

  counts_t * newCounts = createCounts();
  char * line = NULL;
  size_t size = 0;
  while (getline(&line, &size, f) >= 0) {
    char * ptr = strchr(line, '\n');
    char * key = strndup(line, ptr - line);
    char * value = lookupValue(kvPairs, key);
    addCount(newCounts, value);
    free(key);
  }
  free(line);
  if (fclose(f) != 0) {
    perror("Error: cannot close the file");
  }
  return newCounts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    perror("Less argument\n");
    return EXIT_FAILURE;
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kv);

    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    if (f != NULL) {
      printCounts(c, f);
    }

    //close f
    if (fclose(f) != 0) {
      perror("Error: cannot close the file");
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
