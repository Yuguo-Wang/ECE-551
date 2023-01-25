#ifndef _EXPR_H_
#define _EXPR_H_

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  Expression(){};
  virtual std::string toString() const = 0;  //abstract method
  virtual ~Expression(){};
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream res;
    res << num;
    return res.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
  }

  virtual std::string toString() const {
    std::stringstream res;
    res << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return res.str();
  }

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

#endif
