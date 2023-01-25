#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>

//YOUR CODE GOES HERE
class OOB : public std::exception {
 public:
  const char * what() const throw() { return "index out of boundry"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node(T d) : data(d), next(NULL), prev(NULL){};
  };

  Node * head;
  Node * tail;
  int size;

 public:
  //default constructor:
  LinkedList() : head(NULL), tail(NULL), size(0){};
  //copy constructor
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.head;
    while (temp != NULL) {
      addBack(temp->data);
      temp = temp->next;
    }
  }
  //operator=
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList temp(rhs);  //copy constructor
      //deep copy
      std::swap(temp.head, head);
      std::swap(temp.tail, tail);
      std::swap(temp.size, size);
    }
    return *this;
  }

  ~LinkedList() {
    Node * p = head;
    Node * temp = NULL;
    while (p != NULL) {
      temp = p->next;
      delete p;
      p = temp;
    }
  }

  void addFront(const T & item) {
    Node * node = new Node(item);
    if (head != NULL) {
      node->next = head;
      head->prev = node;
      head = node;
    }
    else {
      head = node;
      tail = head;
    }
    size++;
  }

  void addBack(const T & item) {
    Node * node = new Node(item);
    if (tail != NULL) {
      tail->next = node;
      node->prev = tail;
      tail = node;
    }
    else {
      head = node;
      tail = node;
    }
    size++;
  }

  bool remove(const T & item) {
    Node * temp = head;
    while (temp != NULL && temp->data != item) {
      temp = temp->next;
    }
    if (temp == NULL) {
      return false;
    }
    Node * pre = temp->prev;
    Node * nxt = temp->next;

    if (pre != NULL) {
      pre->next = nxt;
    }
    else {
      head = nxt;
    }

    if (nxt != NULL) {
      nxt->prev = pre;
    }
    else {
      tail = pre;
    }
    size--;
    delete temp;
    return true;
  }

  T & operator[](int index) {
    try {
      if (index < 0 || index >= size) {
        throw OOB();
      }
    }
    catch (OOB & data) {
      std::cerr << data.what() << std::endl;  //what() throw
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  const T & operator[](int index) const {
    try {
      if (index < 0 || index >= size) {
        throw OOB();
      }
    }
    catch (OOB & data) {
      std::cerr << data.what() << std::endl;
    }
    Node * temp = head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  int find(const T & item) {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }
  int getSize() const { return size; };
};

/*
class OOB: public std::exception{
public:
  const char * what() const throw(){
    return "Fail";
  }
};
*/

#endif
