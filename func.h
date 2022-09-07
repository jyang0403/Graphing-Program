#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"
#include "color.h"

class Function {
private:
  // a function has a name and an expression computing its value (given x)
  std::string m_name;
  Expr *m_expr;
  //function color
  Color * color;
  bool has_color = false;

  Function(const Function &);
  Function &operator=(const Function &);

public:
  Function(const std::string &name, Expr *expr);
  ~Function();

  std::string get_name() const { return m_name; }
  Expr *get_expr() const       { return m_expr; }
  //color member function
  void set_color(uint32_t r, uint32_t g, uint32_t b);
  Expr* get_expr();
  //getters for color of function itself
  uint32_t get_r();
  uint32_t get_g();
  uint32_t get_b();
  std::string get_name();
  //setter function for function class
  void set_name(std::string name);
  bool color_check();
  void set_color_check(bool check);
};


#endif // FUNC_H
