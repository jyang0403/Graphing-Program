#include "func.h"
#include "color.h"

Function::Function(const std::string &name, Expr *expr)
  : m_name(name)
  , m_expr(expr)
  , color(new Color()) { //initialize function color to white
    color->r = 255;
    color->b = 255;
    color->g = 255;
}

Function::~Function() {
  delete color;
  delete m_expr;
}

//color member function
void Function::set_color(uint32_t r, uint32_t g, uint32_t b) {
  this->color->r = r;
  this->color->g = g;
  this->color->b = b;
}
//check if a function hsa an exisitng color directive
bool Function::color_check() {
  return has_color;
}

//set the boolean to see if a function has an existing color directive
void Function::set_color_check(bool check) {
  has_color = check;
}

//function to get red value
uint32_t Function::get_r() {
  return this->color->r;
}
//function to get green value
uint32_t Function::get_g() {
  return this->color->g;
}
//function to get blue value
uint32_t Function::get_b() {
  return this->color->b;
}
//get expression of a function
Expr* Function::get_expr() {
  return this->m_expr;
}
//get name of a function
std::string Function::get_name() {
  return m_name;
}
//set name of a function
void Function::set_name(std::string name) {
  m_name = name;
}