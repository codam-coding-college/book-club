#include <iostream>

using namespace std;

// Problem:
// Given a linked list, sort it using the merge sort algorithm.

typedef struct node {
  int         val;
  struct node *next;
}             t_node;

// Merges the 2 sorted sublists.
t_node *mergeList(t_node *nodes_a, t_node *nodes_b) {
  // base cases
  if (!nodes_a)
    return (nodes_b);
  if (!nodes_b)
    return (nodes_a);
  
  if (nodes_a->val < nodes_b->val) {
    nodes_a->next = mergeList(nodes_a->next, nodes_b);
    return (nodes_a);
  }
  else {
    nodes_b->next = mergeList(nodes_a, nodes_b->next);
    return (nodes_b);
  }
}

// Use tortoise & hare method to find mid point and
// split the list into 2 sublists.
t_node *splitList(t_node *nodes_a) {
  t_node *mid;
  t_node *fast = nodes_a;
  t_node *slow = nodes_a;

  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  // slow is the element before the midpoint, so we
  // split the list at that point.
  mid = slow->next;
  slow->next = NULL;
  return mid;
}

t_node *mergeSort(t_node *nodes) {
  t_node *nodes_b;

  // base case
  if (!nodes || !nodes->next)
    return (nodes);

  // split larger list into 2 sublists
  nodes_b = splitList(nodes);

  // recursively sort sublists
  nodes = mergeSort(nodes);
  nodes_b = mergeSort(nodes_b);

  // merge the 2 sorted sublists
  return (mergeList(nodes, nodes_b));
}

void printList(t_node *node) {
  while (node != NULL) {
    cout << node->val << " ";
    node = node->next;
  }
  cout << endl;
}

void pushNode(t_node **nodes, int val) {
  t_node *new_node = new t_node();
  new_node->val = val;
  new_node->next = (*nodes);
  (*nodes) = new_node;
}

int main() {
  int keys[] = {6, 8, 4, 3, 1, 9};
  int n = sizeof(keys) / sizeof(keys[0]);

  t_node *nodes = NULL;
  for (int i = 0; i < n; i++) {
    pushNode(&nodes, keys[i]);
  }
  
  cout << "Before sorting: ";
  printList(nodes);
  
  nodes = mergeSort(nodes);
  cout << "After sorting: ";
  printList(nodes);
}
