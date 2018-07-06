#define _GNU_SOURCE
#include "knapsack.h"


Knapsack create_knapsack(char *items_file, float max_weigth, int list_size) {
  Knapsack knapsack;

  knapsack.list_size = list_size;
  knapsack.max_weigth = max_weigth;

  if (max_weigth <= 0 || list_size <= 0) {
    printf("Error on max weight or list size\n");
    return knapsack;
  } else {
    knapsack.item_list = create_item_list(items_file, list_size);

    if (knapsack.item_list == NULL) {
      printf("Error creating the items list\n");
      return knapsack;
    }
  }
  return knapsack;
}
