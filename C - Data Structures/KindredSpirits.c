// Cody Oliver
// COP 3502, Spring 2019
// NID: 3125452

#include "KindredSpirits.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Helper Fucnctions
node *create_node_helper(int data)
{
  // Obtained from webcourse/class notes
  node *n = calloc(1, sizeof(node));
  n->data = data;
  return n;
}

void preOrder(node *root, int *pre_string, int *i)
{
  // Check if root is NULL
  if (root == NULL)
    return;

  // Store preorder string
  pre_string[*i] = root->data;
  *i =  *i + 1;
  preOrder(root->left, pre_string, i);
  preOrder(root->right, pre_string, i);
}

void postOrder(node *root, int *post_string, int *i)
{
  // Check if root is NULL
  if (root == NULL)
    return;

  // Store postorder string
  postOrder(root->left, post_string, i);
  postOrder(root->right, post_string, i);
  post_string[*i] = root->data;
  *i = *i + 1;
}

int sameString(int *pre_string, int *post_string, int a_length, int b_length)
{
  int i;

  // Return false if strings are different lengths
  if (a_length != b_length)
    return 0;

  // Compare each index of the post and pre order
  for (i = 0; i < a_length; i++)
  {
    if (pre_string[i] != post_string [i])
      return 0;
  }

  return 1;
}

int count_nodes(node *root)
{
  // Obtained from webcourse/class notes
  if (root == NULL)
    return 0;
  return 1 + count_nodes(root->left) + count_nodes(root->right);
}


// Primary Functions
int isReflection(node *a, node *b)
{
  // Check if both tree are empty, showing a reflection
  if (a == NULL && b == NULL)
    return 1;

  // Check if only one tree is empty, showing a non reflection
  if (a == NULL || b == NULL)
    return 0;

  // Return true if both trees are reflections
  if (a->data == b->data && isReflection(a->left, b->right) && isReflection(a->right, b->left))
    return 1;

  else return 0;
}

node *makeReflection(node *root)
{
  node *new_root;

  // Check if original root is NULL
  if (root == NULL)
    return NULL;

  // Create new nodes for the copied tree
  new_root = create_node_helper(root->data);

  new_root->left = makeReflection(root->right);
  new_root->right = makeReflection(root->left);

  return new_root;
}

int kindredSpirits(node *a, node *b)
{
  int *pre_a, *post_a, *pre_b, *post_b;
  int index_1 = 0, index_2 = 0, index_3 = 0, index_4 = 0, a_length, b_length;

  // Store numer of nodes in each tree
  a_length = count_nodes(a);
  b_length = count_nodes(b);

  // Allocate space for pre/post strings
  pre_a = malloc(sizeof(int) * a_length);
  post_a = malloc(sizeof(int) * a_length);
  pre_b = malloc(sizeof(int) * b_length);
  post_b = malloc(sizeof(int) * b_length);

  // Call pre/postorder fuctions to populate strings
  preOrder(a, pre_a, &index_1);
  postOrder(a, post_a, &index_2);
  preOrder(b, pre_b, &index_3);
  postOrder(b, post_b, &index_4);

  // Comparison to check for KindredSpirit status, return true or false. Free strings
  if (sameString(pre_a, post_b, a_length, b_length) || sameString(pre_b, post_a, a_length, b_length))
  {
    free(pre_a);
    free(pre_b);
    free(post_a);
    free(post_b);
    return 1;
  }
  else
  {
    free(pre_a);
    free(pre_b);
    free(post_a);
    free(post_b);
    return 0;
  }
}

double difficultyRating(void)
{
  double difficulty;
  difficulty = 4.0;
  return difficulty;
}

double hoursSpent(void)
{
  double hours;
  hours = 8.0;
  return hours;
}
