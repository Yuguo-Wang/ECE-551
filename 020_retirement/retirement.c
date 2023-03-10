#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  for (int i = startAge; i < startAge + working.months + retired.months; i++) {
    int ageYear = i / 12;
    int ageMonth = i % 12;
    printf("Age %3d month %2d you have $%.2lf\n",
           ageYear,
           ageMonth,
           initial);  //Age + Month !!

    if (i < startAge + working.months) {
      initial += working.rate_of_return * initial + working.contribution;
    }
    else {
      initial += retired.rate_of_return * initial + retired.contribution;
    }
  }
  //return balance;
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);
  return 0;
}
