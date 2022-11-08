#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

/* functions to create lists */
node *make_node(int v, node *q) {
  node *p = malloc(sizeof(node));
  p->value = v;
  p->next = q;
  return p;
}

/* free all nodes in the list p */
void free_list(node *p) {
  node *q;
  while (p != NULL) {
    q = p->next;
    free(p);
    p = q;
  }
}

/* print list to console */
void print_list(node *p) {
  // Code for exercise 1 

  if (p == NULL) /* base case */
    return;
  else /*print value and call function again with next element in list*/
  {
    printf("%d ", p->value);
    print_list(p->next);
  }
}


int sum_squares(node *p) {
  // Add your code for excercise 2
  // You can find the tests in tests.cpp
  if (p == NULL) /*base case*/
    return 0; /*nothing to be squared*/
  else
    return p->value * p->value + sum_squares(p->next);
}

typedef int (*fn_int_to_int)(int);

node *map(node *p, fn_int_to_int f) { 
  // Add your code for excercise 3

  node *temp = malloc(sizeof(node)); //use malloc to create new node in answer list

  if (p == NULL) /* Base case */
    return NULL; 
  else 
  {
    temp->value = f(p->value); /* gives new node in answer list the correct value */
    temp->next = map(p->next, f); /* will make the new node in answer list point to next node in answer list */
    return temp; /* returns pointer to head of answer list */
  } 
}

int square(int x) { return x * x; }

// example of another function that can be passed to map
// returns the sign of the number
// -1 if negative, 0 if zero, 1 if positive
int sign(int x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
