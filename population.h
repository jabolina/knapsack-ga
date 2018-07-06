#include "knapsack.h"
#include "individual.h"


typedef struct population {
  Individual *individuals;
  int chromossomes_length;
  int population_size;
  int population_nb;
  float retention;
  float mutation;
  Knapsack knapsack;
} Population;


void create_first_population(Knapsack knapsack, Population *population);
