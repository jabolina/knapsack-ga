#define _GNU_SOURCE
#include "population.h"
#include <time.h>

void create_first_population(Knapsack knapsack, Population *population) {
  int i, j, chromossomes_length;

  chromossomes_length = knapsack.list_size;
  srand(time(NULL));


  population->population_nb = 0;
  population->individuals = (Individual*)malloc(population->population_size*sizeof(Individual));

  for (i=0; i<population->population_size; i = i+1) {
  population->individuals[i].chromossomes = (int*)malloc(chromossomes_length * sizeof(int));

  for (j=0; j<chromossomes_length; j = j+1) {
    population->individuals[i].chromossomes[j] = rand() > 0.5 ? 1 : 0;
  }

  population->individuals[i].chromossome_length = chromossomes_length;
  }
}
