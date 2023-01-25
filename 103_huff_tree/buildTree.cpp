#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!

  priority_queue_t pq;
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }

  while (pq.size() != 1) {
    Node * first = pq.top();
    pq.pop();
    Node * second = pq.top();
    pq.pop();

    Node * newNode = new Node(first, second);
    pq.push(newNode);
  }
  Node * root = pq.top();
  return root;
}
