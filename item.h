#include <stdio.h>
#include <stdlib.h>

typedef struct item_ {
  float weight;
  float value;
} Item;


Item* create_item_list(char *file_name, int item_nb);
