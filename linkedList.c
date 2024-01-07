#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

typedef struct node {
    char word[50];
    int occurrences;
    int line;
    struct node *next;
} Node;

struct list {
  Node * head; 
};