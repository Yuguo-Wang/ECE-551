#include "pandemic.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  if (line != NULL) {
    if (strlen(line) == 0) {
      printf("Error: The information is empty");
      exit(EXIT_FAILURE);
    }
  }
  else {
    printf("Error: The line is NULL");
    exit(EXIT_FAILURE);
  }

  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // split the line by the comma
  const char * comma = ",";
  char * name_of_line = strtok(line, comma);
  char * population_char = strtok(NULL, comma);

  // find that the population are all numbers
  //if (strspn(population_char, "0123456789") != strlen(population_char)) {
  //printf("Error: the data of population are not all numbers");
  //exit(EXIT_FAILURE);
  //}

  // To change char to unsigned long
  char * pEnd;
  uint64_t population_of_line = strtol(population_char, &pEnd, 0);

  if (strlen(name_of_line) >= 64) {  // no '\0'
    printf("The data has wrong type.\n(Hint: char name[64])");
    exit(EXIT_FAILURE);
  }
  if (population_of_line < 0) {
    printf("The input has wrong type.\n(Hint: Positive integer)");
    exit(EXIT_FAILURE);
  }
  if (population_of_line > ULLONG_MAX) {  //pow(2, 64) - 1
    printf("Error: The uint64_t data is out of range");
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
    printf("Error: The data of days is less than 7 days");
    exit(EXIT_FAILURE);
  }

  int curr = 0;
  for (size_t i = 0; i < n_days - 6; i++) {
    unsigned sum = 0;
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
    printf("Error: The data of days should exceed 0");
    exit(EXIT_FAILURE);
  }

  if (pop <= 0) {
    printf("Error: The divisor cannot be 0 and population should be positive");
    exit(EXIT_FAILURE);
  }

  if (data == NULL || cum == NULL) {
    printf("Error: The data is empty");
    exit(EXIT_FAILURE);
  }

  if (pop > ULLONG_MAX) {  // pow(2, 64) - 1
    printf("Error: The uint64_t data is out of range");
    exit(EXIT_FAILURE);
  }

  cum[0] = data[0] * 100000 / (double)pop;
  for (size_t i = 1; i < n_days; i++) {
    data[i] = data[i - 1] + data[i];

    double data_per_pop = data[i] * 100000 / (double)pop;
    cum[i] = data_per_pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_days < 1 || n_countries < 1) {
    printf("Error: The data pf counties and days should be positive");
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
    printf("The data has wrong type.\n(Hint: char name[64])");
    exit(EXIT_FAILURE);
  }

  printf("%s has the most daily cases with %u\n", country_name, number_cases);
}
