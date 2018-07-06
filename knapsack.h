#include "item.h"

typedef struct knapsack {
  Item* item_list;
  float max_weigth;
  int list_size;
} Knapsack;


Knapsack create_knapsack(char *items_file, float max_weigth, int list_size);
