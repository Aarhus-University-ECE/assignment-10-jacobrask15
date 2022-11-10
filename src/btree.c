#include "btree.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void placerer_men_returner_intet(int x, struct tree_node *t) {
  
/*havde først lavet denne funktion men kunne ikke se hvor den skulle returne root igen, 
  så nu bruger jeg den til at placere x i min insert hvis træet ikke er tomt */

    if (x <= t->item) /* new node must be placed left of root*/
    {
      if (t->left == NULL) /*This is where new node must be placed*/
      {
        /*Creates new node to the left*/
        struct tree_node *new_left = malloc(sizeof(struct tree_node));
        new_left->item = x;
        new_left->left = NULL;
        new_left->right = NULL;
        t->left = new_left;
      }
      else  /*we can use recursion and call insert function again with roots left as input*/
      {
        placerer_men_returner_intet(x, t->left);
      }
    }
    else /* new node must be placed right of root*/
    {
      if (t->right == NULL) /*This is where new node must be placed*/
      {
        /*Creates new node to the right*/
        struct tree_node *new_right = malloc(sizeof(struct tree_node));
        new_right->item = x;
        new_right->left = NULL;
        new_right->right = NULL;
        t->right = new_right;
      }
      else  /*we can use recursion and call insert function again with roots right as input*/
      {
        placerer_men_returner_intet(x, t->right);
      }
    }
  }
  

struct tree_node *Insert(int x, struct tree_node *t) {

  /*when tree is empty insert x into the empty node created by the initialize function*/
  if (t->item == 0) 
  {
    t->item = x;
    return t;
  }
  else /*place new node the correct place and return root*/ 
  {
    placerer_men_returner_intet(x, t);

    return t;
  }
}

struct tree_node *Remove(int x, struct tree_node *t) {
  
  if (!Contains(x, t)) /*if x is not in tree do nothing*/
    return t;
  
  struct tree_node *kopit = t;
  struct tree_node **temp2 = &t;

  /*First find where x is*/
  while(kopit->item != x)
  {
    if (x < kopit->item) /*x is further to the left*/
    {
      kopit = kopit->left;
      temp2 = &((*temp2)->left);
    }
    else if (x > kopit->item) /*x is further to the right*/
    {
      kopit = kopit->right;
      temp2 = &((*temp2)->right);
    }
  }

  /*now temp->item is equal to x, and we know which node to remove*/
  /*temp2 is pointing to the pointer that is pointing to the node where x is*/
  /*Now it is time to figure out what should replace the node with x*/
  /*It should be the node with the largest x, left of the node with x*/

  if (kopit->left == NULL && kopit->right == NULL) /*When x is in a leaf*/
  {
    *temp2 = NULL;
    free(kopit);
  }
  if (kopit->left == NULL && kopit->right != NULL) /*x node should just be replaced with node to the right*/
  {
    *temp2 = kopit->right;
    free(kopit);
  }
  if (kopit->left != NULL && kopit->right == NULL) /*x node should just be replaced with node to the left*/
  {
    *temp2 = kopit->left;
    free(kopit);
  }
  if (kopit->left != NULL && kopit->right != NULL) /*x node should be replaced with the node containing the biggest number smaller than x*/
  {
    /*First find the node to replace node with x*/
    struct tree_node *kopit2 = kopit->left;
    struct tree_node **temp3 = &kopit->left; 

    while (kopit2->right != NULL)
    {
      kopit2 = kopit2->right;
      temp3 = &((*temp3)->right);
    }

    /*Now kopit2 is the node with biggest number smaller than x and temp3 is a pointer that points to the pointer that points to kopit2*/
    *temp2 = kopit2;
    kopit2->left = kopit->left;
    kopit2->right = kopit->right;
    free(kopit);
    *temp3 = NULL;
}

return t;
}

int Contains(int x, struct tree_node *t) {

  if (t->item == 0) /*x will not be in an empty tree*/
  {
    return 0;
  }
  else
  {
    if (x == t->item) /*x is in root*/
    {
      return 1;
    }
    else if (x < t->item) /*x is left of root*/
    {
      if (t->left == NULL) /*in the case that there is nothing left of root*/
      {
        return 0; 
      }
      else
      {
      Contains(x, t->left); /*if there is something left of root, call function with that as new root*/
      }
    }
    else /* x is right of root*/
    {
      if (t->right == NULL)
      {
        return 0;
      }
      else
      {
        Contains(x, t->right);
      }
    }
  }
}

struct tree_node *Initialize(struct tree_node *t) {
  // Create an empty tree

  t = (struct tree_node*)malloc(sizeof(struct tree_node)); 

  t->item = 0;
  t->left = NULL;
  t->right = NULL;

  return t;
}

int Empty(struct tree_node *t) {
  // Test if empty
  if (t->item == 0)
    return 1;
  else
    return 0;
}

int Full(struct tree_node *t) {
  // Test if full
  return 0;
}
