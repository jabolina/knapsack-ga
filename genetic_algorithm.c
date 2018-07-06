#define _GNU_SOURCE
#include "genetic_algorithm.h"

typedef struct tuple {
  int fitness_value;
  int list_index;
} Tuple;

void remove_random_item(Individual *individual) {
  int i, removed = 0;

  while (!removed) {
    i = (rand() % individual->chromossome_length);
    if (individual->chromossomes[i]) {
      individual->chromossomes[i] = 0;
      removed = 1;
    }
  }
}

void order_individuals(Individual *individuals, Individual *ordered, Tuple *how,
                       int size) {

  int i;

  for (i=0; i<size; i = i+1) {
    ordered[i] = individuals[how[i].list_index];
  }
}

void bubble_sort(Tuple *order, int size) {
  int i, j;
  Tuple aux;

  for (i=0; i<size; i = i+1) {
    for (j=i+1; j<size; j = j+1) {
      if (order[j].fitness_value > order[i].fitness_value) {
         aux = order[j];
         order[j] = order[i];
         order[i] = aux;
      }
    }
  }
}

Individual new_child(Individual father1, Individual father2) {
  int i;
  Individual child;
  child.chromossome_length = father1.chromossome_length;
  child.chromossomes = (int*)malloc(father1.chromossome_length*sizeof(int));

  for (i=0; i<child.chromossome_length; i=i+1) {
    child.chromossomes[i] = (rand() > 0.5) ? father1.chromossomes[i] :
                                             father2.chromossomes[i];
  }
  return child;
}

float fitness(Individual *individual, Knapsack knapsack) {
  int i;
  float weight, value;

  weight = 0.0;
  value = 0.0;

  for (i=0; i<individual->chromossome_length; i++) {
    if (individual->chromossomes[i]) {
      weight = weight + knapsack.item_list[i].weight;
      value = value + knapsack.item_list[i].value;
    }
  }

  if (weight > knapsack.max_weigth) {
    remove_random_item(individual);
    return -1.0;
  }
  return value;
}

void mutate(Individual individual, int size) {
  int index;

  index = (rand() % size);
  individual.chromossomes[index] = 1 - individual.chromossomes[index];
}

void cross_over(Individual *fathers, Population *population) {
  int actual_size = (population->population_size * population->retention) + 1;
  Individual father1, father2, child;

  free(population->individuals);
  population->individuals = fathers;

  while (actual_size < population->population_size) {
    father1 = fathers[(rand() % population->population_size)];
    father2 = fathers[(rand() % population->population_size)];

    child = new_child(father1, father2);
    if (rand() > population->mutation) {
      mutate(child, child.chromossome_length);
    }
    population->individuals[actual_size++] = child;

    child = new_child(father1, father2);
    if (rand() > population->mutation) {
      mutate(child, child.chromossome_length);
    }
    population->individuals[actual_size++] = child;
  }
}

Individual *order_by_fit(Population *population) {
  int i;
  float aux = -1.0;
  Individual *ordered = (Individual*)malloc(population->population_size*sizeof(Individual));
  Tuple *values = (Tuple*)malloc(population->population_size*sizeof(Tuple));

  for (i=0; i<population->population_size; i = i+1) {
    values[i].list_index = i;
    while (aux < 0) {
      aux = fitness(&(population->individuals[i]), population->knapsack);
    }
    values[i].fitness_value = aux;
    population->individuals[i].fitness_value = aux;
  }

  order_individuals(population->individuals, ordered, values, population->population_size);

  return ordered;
}

void evolve(Population *population) {
  if (population == NULL) {
    return ;
  } else {
    Individual *ordered = order_by_fit(population);
    cross_over(ordered, population);
  }
}
