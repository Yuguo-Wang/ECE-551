#include "node.h"

void backtrack(BitString b, std::map<unsigned, BitString> & theMap, Node * curr) {
  if (curr == NULL) {
    return;
  }

  if (curr->sym == NO_SYM) {
    backtrack(b.plusZero(), theMap, curr->left);
    backtrack(b.plusOne(), theMap, curr->right);
  }
  else {
    assert(curr->left == NULL && curr->right == NULL);
    theMap.insert(std::pair<unsigned, BitString>(curr->sym, b));
  }
}

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  backtrack(b.plusZero(), theMap, left);
  backtrack(b.plusOne(), theMap, right);
}
