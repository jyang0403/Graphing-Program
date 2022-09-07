#ifndef EXPR_H
#define EXPR_H

#include <vector>
#include <cmath>

// Base expression class
class Expr {
private:
  Expr(const Expr &);
  Expr &operator=(const Expr &);
public:
  Expr();
  virtual ~Expr();
  //contains all child nodes
  std::vector<Expr*> children;
  void add_child(Expr * expression);
  //recursive evaluation of all child nodes and descendants for each operation
  virtual double eval(double x) const = 0;
};

//derived expression classes
class X : public Expr {
  public:
    X();
    ~X();
    double eval(double x) const;
};

class Pi : public Expr {
  public:
    Pi();
    ~Pi();
    const double PI = M_PI;
    double eval(double x) const;
};

class Literal : public Expr {
  public:
    Literal();
    Literal(double val);
    ~Literal();
    double eval(double x) const;
  private:
    double value;
};

class Sin : public Expr {
  public:
    Sin();
    ~Sin();
    double eval(double x) const;
};

class Cos : public Expr {
  public:
    Cos();
    ~Cos();
    double eval(double x) const;
};

class Add : public Expr {
  public:
    Add();
    ~Add();
    double eval(double x) const;
    double sum_children();
};

class Subtract : public Expr {
  public:
    Subtract();
    ~Subtract();
    double eval(double x) const;
};

class Multiply : public Expr {
  public:
    Multiply();
    ~Multiply();
    double eval(double x) const;
};

class Divide : public Expr {
  public:
    Divide();
    ~Divide();
    double eval(double x) const;
};
#endif // EXPR_H
