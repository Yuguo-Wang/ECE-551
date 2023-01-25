/*
#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    const IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    //[]
    IntList case1;
    assert(case1.head == NULL && case1.tail == NULL && case1.getSize() == 0);
    //[1]
    case1.addFront(1);
    assert(case1.head->data == 1 && case1.tail->data == 1 && case1.getSize() == 1 &&
           case1.tail->prev == NULL && case1.head->next == NULL &&
           case1.head->prev == NULL && case1.tail->next == NULL);
    //[3,1]
    case1.addFront(3);
    assert(case1.getSize() == 2);
    assert(case1.head->data == 3);
    assert(case1.head->next->data == 1);
    assert(case1.tail->data == 1);
    assert(case1.head->prev == NULL && case1.tail->next == NULL &&
           case1.tail->prev->data == 3);
    //[4,3,1]

    case1.addFront(4);
    assert(case1.head->data == 4);
    assert(case1.head->prev == NULL);
    assert(case1.head->next->data == 3);
    assert(case1.head->next->next->data == 1);
    assert(case1.head->next->next->prev->prev->data == 4);
    assert(case1.head->next->next->next == NULL);
    assert(case1.tail->data == 1);
    assert(case1.tail->next == NULL);
    assert(case1.tail->prev->data == 3);
    assert(case1.tail->prev->prev->data == 4);
    assert(case1.tail->prev->prev->next->next->data == 1);
    assert(case1.tail->prev->prev->prev == NULL);
    assert(case1.getSize() == 3);
  }

  void testAddBack() {
    // many more tester methods
    IntList case1;
    assert(case1.head == NULL && case1.tail == NULL && case1.getSize() == 0);
    //[1]
    case1.addBack(1);
    assert(case1.head->data == 1 && case1.tail->data == 1 && case1.getSize() == 1 &&
           case1.tail->prev == NULL && case1.head->next == NULL &&
           case1.head->prev == NULL && case1.tail->next == NULL);
    //[1,3]
    case1.addBack(3);
    assert(case1.getSize() == 2 && case1.head->data == 1 && case1.head->next->data == 3 &&
           case1.tail->data == 3 && case1.head->prev == NULL &&
           case1.tail->next == NULL && case1.tail->prev->data == 1);
  }

  void testRemove() {
    IntList case1;
    //[1,2,3]
    case1.addBack(1);
    case1.addBack(2);
    case1.addBack(3);

    case1.remove(3);
    assert(case1.head->data == 1 && case1.head->prev == NULL &&
           case1.head->next->data == 2 && case1.head->next->next->data == 3 &&
           case1.head->next->next->prev->prev->data == 1 &&
           case1.head->next->next->next == NULL);
    assert(case1.tail->data == 3 && case1.tail->next == NULL &&
           case1.tail->prev->data == 2 && case1.tail->prev->prev->data == 1 &&
           case1.tail->prev->prev->next->next->data == 3 &&
           case1.tail->prev->prev->prev == NULL && case1.getSize() == 3);

    //[1,2]
    assert(!case1.remove(3));
    
  }

  void testCopy() {
    IntList case1;
    IntList case2(case1);
    assert(case2.head == NULL && case2.tail == NULL && case2.getSize() == 0);

    IntList * case3 = new IntList();
    case3->addBack(1);
    case3->addBack(2);

    IntList * case4 = new IntList(*case3);
    assert(case3 != case4);
    case3->remove(2);
    assert((*case4)[0] == 1);
    delete case3;
    assert((*case4)[0] == 1);
    delete case4;
  }

  void testAssign() {
    IntList * case1 = new IntList();
    IntList * case2 = new IntList();
    //[1,2,3]
    case1->addBack(1);
    case1->addBack(2);
    case1->addBack(3);
    //[4,5,6]
    case2->addBack(4);
    case2->addBack(5);
    case2->addBack(6);

    *case2 = *case1;
    assert(case1 != case2);
    case1->remove(3);
    assert((*case2)[2] == 3);
    delete case1;

    assert(case2->getSize() == 3);
    delete case2;
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  //t.testRemove();
  //t.testCopy();
  //t.testAssign();

  
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
*/

#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }

  void testCopy() {
    IntList il;
    IntList il2(il);
    assert(il2.head == NULL);
    assert(il2.tail == NULL);
    assert(il2.getSize() == 0);

    IntList * il3 = new IntList();
    il3->addBack(1);
    il3->addBack(2);
    il3->addBack(3);  //0
    //il3->addBack(4);

    IntList * il4 = new IntList(*il3);
    assert(il3 != il4);
    il3->remove(1);
    assert(((*il4)[0] == 1));
    delete il3;
    assert(((*il4)[0] == 1));
    delete il4;
  }

  void testAssign() {
    IntList * il = new IntList();
    IntList * il2 = new IntList();
    il2->addBack(5);
    il2->addBack(6);
    il2->addBack(7);
    il2->addBack(8);

    il->addBack(1);
    il->addBack(2);
    il->addBack(3);
    il->addBack(4);
    *il2 = *il;
    assert(il2 != il);
    il->remove(3);
    assert((*il2)[2] == 3);
    delete il;
    assert(il2->getSize() == 4);
    delete il2;
  }

  void testAddFront() {
    IntList il;
    il.addFront(1);
    assert(il.head->data == 1);
    assert(il.tail->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.getSize() == 1);

    il.addFront(2);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 1);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
    assert(il.getSize() == 2);

    il.addFront(3);
    assert(il.head->data == 3);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
    assert(il.head->next->next->data == 1);
    assert(il.head->next->next->prev->prev->data == 3);
    assert(il.head->next->next->next == NULL);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
    assert(il.tail->prev->prev->data == 3);
    assert(il.tail->prev->prev->next->next->data == 1);
    assert(il.tail->prev->prev->prev == NULL);
    assert(il.getSize() == 3);
  }

  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(il.head->data == 1);
    assert(il.tail->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.getSize() == 1);

    il.addBack(2);
    assert(il.head->data == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
    assert(il.tail->data == 2);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 1);
    assert(il.getSize() == 2);

    il.addBack(3);
    assert(il.head->data == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
    assert(il.head->next->next->data == 3);
    assert(il.head->next->next->prev->prev->data == 1);
    assert(il.head->next->next->next == NULL);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
    assert(il.tail->prev->prev->data == 1);
    assert(il.tail->prev->prev->next->next->data == 3);
    assert(il.tail->prev->prev->prev == NULL);
    assert(il.getSize() == 3);
  }

  void testRemove() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    il.addBack(3);
    il.addBack(4);
    il.addBack(4);

    il.remove(4);
    assert((il[0] == 1) && (il[1] == 2) && (il[2] == 3) && (il[3] == 4));
    il.remove(4);
    assert(il.head->data == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
    assert(il.head->next->next->data == 3);
    assert(il.head->next->next->prev->prev->data == 1);
    assert(il.head->next->next->next == NULL);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
    assert(il.tail->prev->prev->data == 1);
    assert(il.tail->prev->prev->next->next->data == 3);
    assert(il.tail->prev->prev->prev == NULL);
    assert(il.getSize() == 3);
    il.remove(1);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 3);
    assert(il.tail->data == 3);
    assert(il.tail->next == NULL);
    assert(il.tail->prev->data == 2);
    assert(il.getSize() == 2);
    il.remove(2);
    assert(il.head->data == 3);
    assert(il.tail->data == 3);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.getSize() == 1);
    il.remove(3);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);

    il.addBack(1);
    il.addBack(1);
    il.addBack(2);
    assert(!il.remove(3));
    il.remove(1);
    assert((il[0] == 1) && (il[1] == 2));
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testCopy();
  t.testAssign();
  t.testAddFront();
  t.testAddBack();
  t.testRemove();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
