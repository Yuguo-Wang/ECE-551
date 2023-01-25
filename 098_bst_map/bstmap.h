#include <cstdlib>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class TreeNode {
   public:
    K key;
    V value;
    TreeNode * left;
    TreeNode * right;
    TreeNode() : key(0), value(0), left(NULL), right(NULL){};
    TreeNode(K k, V v) : key(k), value(v), left(NULL), right(NULL){};
  };

  TreeNode * root;

  TreeNode ** minKey_Right(TreeNode ** curr) {
    curr = &((*curr)->right);
    while ((*curr)->left != NULL) {
      curr = &((*curr)->left);
    }
    return curr;
  }

 public:
  BstMap() : root(NULL){};
  TreeNode * copy(const TreeNode * curr) {
    if (curr == NULL) {
      return NULL;
    }
    TreeNode * node = new TreeNode(curr->key, curr->value);
    node->left = copy(curr->left);
    node->right = copy(curr->right);
    return node;
  }
  //copy constructor
  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }
  //assign operator
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) {
    TreeNode ** curr = &root;
    while (*curr != NULL) {
      if ((*curr)->key == key) {
        (*curr)->value = value;
        return;
      }
      else if ((*curr)->key < key) {
        curr = &((*curr)->right);
      }
      else {
        curr = &((*curr)->left);
      }
    }
    *curr = new TreeNode(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    TreeNode * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return curr->value;
      }
      if (curr->key < key) {
        curr = curr->right;
      }
      else {
        curr = curr->left;
      }
    }
    throw std::invalid_argument("Cannot find the invalid key!");
  }

  virtual void remove(const K & key) {
    TreeNode ** curr = &root;
    while (*curr != NULL) {
      if ((*curr)->key == key) {
        TreeNode * temp = *curr;
        if ((*curr)->left == NULL) {
          *curr = temp->right;
          delete temp;
          return;
        }
        if ((*curr)->right == NULL) {
          *curr = temp->left;
          delete temp;
          return;
        }

        TreeNode ** move = minKey_Right(curr);
        temp = *curr;
        *curr = *move;
        *move = (*move)->right;
        (*curr)->left = temp->left;
        (*curr)->right = temp->right;
        delete temp;
        return;
      }
      else if ((*curr)->key < key) {
        curr = &((*curr)->right);
      }
      else {
        curr = &((*curr)->left);
      }
    }
  }
  void deleteTree(TreeNode * curr) {
    if (curr == NULL) {
      return;
    }
    deleteTree(curr->left);
    deleteTree(curr->right);
    delete curr;
  }

  virtual ~BstMap<K, V>() {
    deleteTree(root);
    root = NULL;
  }
};
