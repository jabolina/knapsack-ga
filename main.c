#include "genetic_algorithm.h"

int main(int argc, char *argv[]) {
  int i;
  Population population;
  Knapsack knapsack;
  Individual *individuals;

  knapsack = create_knapsack("./items.txt", 32.5, 10);

  population.chromossomes_length = knapsack.list_size;
  population.population_size = 50;
  population.retention = 0.5;
  population.mutation = 0.75;
  population.knapsack = knapsack;

  create_first_population(knapsack, &population);

  for (i=0; i<30; i++) {
    evolve(&population);
  }

  individuals = order_by_fit(&population);

  printf("%f\n", individuals[0].fitness_value);

  for (i=0; i<population.chromossomes_length; i++) {
    printf("%d", individuals[0].chromossomes[i]);
  }

  return 1;
}
