#include <cstdlib>
#include <stdexcept>

#include "assert.h"
#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  class TreeNode {
   public:
    T key;

    TreeNode * left;
    TreeNode * right;
    TreeNode() : key(0), left(NULL), right(NULL){};
    TreeNode(T t) : key(t), left(NULL), right(NULL){};
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
  BstSet() : root(NULL){};
  TreeNode * copy(const TreeNode * curr) {
    if (curr == NULL) {
      return NULL;
    }
    TreeNode * node = new TreeNode(curr->key);
    node->left = copy(curr->left);
    node->right = copy(curr->right);
    return node;
  }
  //copy constructor
  BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }
  //assign operator
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }

  virtual void add(const T & t) {
    TreeNode ** curr = &root;
    while (*curr != NULL) {
      if ((*curr)->key == t) {
        return;
      }
      else if ((*curr)->key < t) {
        curr = &((*curr)->right);
      }
      else {
        curr = &((*curr)->left);
      }
    }
    *curr = new TreeNode(t);
  }
  virtual bool contains(const T & key) const {
    TreeNode * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return true;
      }
      if (curr->key < key) {
        curr = curr->right;
      }
      else {
        curr = curr->left;
      }
    }
    return false;
    //throw std::invalid_argument("Cannot find the invalid key!");
  }

  virtual void remove(const T & key) {
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

  virtual ~BstSet<T>() {
    deleteTree(root);
    root = NULL;
  }
};
