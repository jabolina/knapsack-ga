#define _GNU_SOURCE
#include "item.h"
#include <string.h>

Item* create_item_list(char *file_name, int item_nb) {
  int i=0;
  char *line = NULL;
  char *tokenized = NULL;
  size_t parameter = 0;

  if (item_nb <= 0) {
    return NULL;
  } else {
    Item *item_list = (Item*)malloc(item_nb * sizeof(Item));

    if (item_list == NULL) {
      printf("Item list allocation error!\n");
      return NULL;
    } else {
      FILE* fp = fopen(file_name, "r");

      if (fp == NULL) {
        printf("Error opening the file %s\n", file_name);
        return NULL;
      } else {
        while ((getline(&line, &parameter, fp)) != -1 && i < item_nb) {
          tokenized = strtok(line, ",");

          item_list[i].weight = atof(tokenized);
          tokenized = strtok(NULL, ",");
          item_list[i].value = atof(tokenized);
          tokenized = strtok(NULL, ",");
          i = i + 1;
        }
      }
      fclose(fp);
    }
    return item_list;
  }
}
