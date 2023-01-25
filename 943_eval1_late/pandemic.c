#include "pandemic.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  if (line != NULL) {
    if (strlen(line) == 0) {
      fprintf(stderr, "The information is empty");
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "The line is NULL");
    exit(EXIT_FAILURE);
  }

  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // split the line by the comma
  const char * comma = ",";
  if (*line == ',') {
    fprintf(stderr, "no country name found");
    exit(EXIT_FAILURE);
  }

  char * name_of_line = strtok(line, comma);
  char * population_char = strtok(NULL, comma);

  // To change char to unsigned long
  char * pEnd;
  uint64_t population_of_line = strtol(population_char, &pEnd, 0);

  if (strlen(name_of_line) >= 64) {  // no '\0'
    fprintf(stderr, "The data has wrong type.\n(Hint: char name[64])");
    exit(EXIT_FAILURE);
  }
  if (population_of_line <= 0) {
    fprintf(stderr, "The input has wrong type.\n(Hint: Positive integer)");
    exit(EXIT_FAILURE);
  }
  if (population_of_line > ULLONG_MAX) {  //pow(2, 64) - 1
    fprintf(stderr, "The uint64_t data is out of range");
    exit(EXIT_FAILURE);
  }

  // Store char into ans.name
  strcpy(ans.name, name_of_line);
  ans.population = population_of_line;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days < 7) {
    fprintf(stderr, "The data of days is less than 7 days");
    exit(EXIT_FAILURE);
  }

  int curr = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    // use sum to calculate the sum and update in the recusion
    double sum = 0;
    int day = curr;

    while (curr < day + 7) {
      sum += data[curr];
      curr++;
    }
    curr -= 6;
    avg[i] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (n_days < 1) {
    fprintf(stderr, "The data of days should exceed 0");
    exit(EXIT_FAILURE);
  }

  if (pop <= 0) {
    fprintf(stderr, "The divisor cannot be 0 and population should be positive");
    exit(EXIT_FAILURE);
  }

  if (data == NULL || cum == NULL) {
    fprintf(stderr, "The data is empty");
    exit(EXIT_FAILURE);
  }

  if (pop > ULLONG_MAX) {  // pow(2, 64) - 1
    fprintf(stderr, "The uint64_t data is out of range");
    exit(EXIT_FAILURE);
  }

  unsigned sum_data = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum_data += data[i];

    double data_per_pop = sum_data / (double)pop * 100000;
    cum[i] = data_per_pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_days < 1 || n_countries < 1) {
    fprintf(stderr, "The data pf counties and days should be positive");
    exit(EXIT_FAILURE);
  }

  char * country_name;
  unsigned number_cases = 0;
  int index = 0;

  // To find the global maximum in the data
  for (size_t i = 0; i < n_days; i++) {         // 32
    for (size_t j = 0; j < n_countries; j++) {  // 9
      if (number_cases <= data[j][i]) {
        number_cases = data[j][i];
        index = (int)j;
      }
    }
  }
  country_name = countries[index].name;

  if (strlen(country_name) >= 64) {  // no '\0'
    fprintf(stderr, "The data has wrong type.\n(Hint: char name[64])");
    exit(EXIT_FAILURE);
  }

  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
