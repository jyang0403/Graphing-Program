#include <cmath>
#include "exception.h"
#include "expr.h"

// Expr (base class)

Expr::Expr() {
}

Expr::~Expr() {
  for(std::vector<Expr*>::iterator itr = children.begin(); itr != children.end(); ++itr) {
    delete *itr;
  }
  this->children.clear();
}
//adds a child to an expression node
void Expr::add_child(Expr * expression) {
  this->children.push_back(expression);
}


X::X() {}
X::~X() {} 
//evaluates for an x, basically just returns x
double X::eval(double x) const { 
  if (this->children.size() != 0) {
    throw PlotException("Error: X must be a leaf node\n");
  }
  return x; 
}

Pi::Pi() {}
Pi::~Pi() {} 
// if pi, return pi
double Pi::eval(double x) const { 
  if (this->children.size() != 0) {
    throw PlotException("Error: pi must be a leaf node\n");
  }
  double dump = x;
  dump--;
  return PI; 
}

Literal::Literal() {}
Literal::Literal(double val) { value = val; }
Literal::~Literal() {}

//return the literal value
double Literal::eval(double x) const {
  if (this->children.size() != 0) {
    throw PlotException("Error: literal must be a leaf node\n");
  }
  double dump = x;
  dump--;
  return value;
}

Sin::Sin() {}
Sin::~Sin() {}
//evaluate sin
double Sin::eval(double x) const { 
  double res = 0;
  //check to see if sin has 1 argument
  if (this->children.size() != 1) {
    throw PlotException("Error: invalid number of arguments for sin\n");
  }
  //calculate total of all sin children/descendants recursively if applicable
  for (Expr* i : this->children) {
    res += i->eval(x);
  }
  return sin(res); 
}

Cos::Cos() {}
Cos::~Cos() {}
double Cos::eval(double x) const { 
  double res = 0;
  //check to see if cos has 1 argument
  if (this->children.size() != 1) {
    throw PlotException("Error: invalid number of arguments for cos\n");
  }
  //calculate total of all cos children/descendants recursively if applicable
  for (Expr* i : this->children) {
    res += i->eval(x);
  }
  return cos(res); 
}

Add::Add() {}
Add::~Add() {}
//add any number of descendants, recursively summing their descendants
double Add::eval(double x) const {
  double sum = 0;
  for (Expr* i : this->children) {
    sum += i->eval(x);
  }
  return sum;
};


Subtract::Subtract() {}
Subtract::~Subtract() {}
//subtract exactly two nodes, recursively if they have descendants
double Subtract::eval(double x) const {
  if (this->children.size() != 2) {
    throw PlotException("Error: Subtraction should have exactly two arguments\n");
  }
  return this->children.front()->eval(x) - this->children.back()->eval(x);
}


Multiply::Multiply() {}
Multiply::~Multiply() {}
//multiply any number of children, recursively if they have descendants
double Multiply::eval(double x) const {
  double sum = 1;
  for (Expr* i : this->children) {
    sum *= i->eval(x);
  }
  return sum;
}

Divide::Divide() {}
Divide::~Divide() {}
//divide exactly two children, recursively if they have descendants
double Divide::eval(double x) const {
  if (this->children.size() != 2) {
    throw PlotException("Error: Division should have exactly two arguments\n");
  }
  if (this->children.back()->eval(x) == 0) {
     throw PlotException("Error: Division by zero\n");
  }
  return this->children.front()->eval(x) / this->children.back()->eval(x);
}