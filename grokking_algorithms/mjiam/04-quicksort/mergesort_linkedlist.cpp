#include <iostream>

typedef struct node {
  int val;
  struct node *next;
} t_node;

t_node *mergeList(t_node *nodes_a, t_node *nodes_b) {
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

// Use tortoise & hare method to find mid point.
t_node *splitList(t_node *nodes_a) {
  t_node *fast;
  t_node *slow;
  t_node *mid;

  fast = nodes_a;
  slow = nodes_a;
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  mid = slow->next;
  slow->next = NULL;
  return mid;
}

t_node *mergeSort(t_node *nodes) {
  t_node *nodes_b;

  // base case
  if (!nodes || !nodes->next)
    return (nodes);

  nodes_b = splitList(nodes);

  nodes = mergeSort(nodes);
  nodes_b = mergeSort(nodes_b);
  return (mergeList(nodes, nodes_b));
}

void printList(t_node *node) {
  while (node != NULL) {
    std::cout << node->val << " ";
    node = node->next;
  }
  std::cout << std::endl;
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
  
  std::cout << "Before sorting: ";
  printList(nodes);
  
  nodes = mergeSort(nodes);
  std::cout << "After sorting: ";
  printList(nodes);
}
