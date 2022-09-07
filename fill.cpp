#include <cassert>
#include "fill.h"

Fill::Fill() : opacity(1), r(0), g(0), b(0) {}
Fill::Fill(float opacity, uint32_t red, uint32_t green, uint32_t blue) : opacity(opacity), r(red), g(green), b(blue) {}
Fill::~Fill() {}

//subclass constructor fillabove
FillAbove::FillAbove(Function &func, float opacity, uint32_t red, uint32_t green, uint32_t blue) : Fill(opacity, red, green, blue), func(&func) {}
FillAbove::~FillAbove() {}

//subclass constructor fillbelow
FillBelow::FillBelow(Function &func, float opacity, uint32_t red, uint32_t green, uint32_t blue) : Fill(opacity, red, green, blue), func(&func) {}
FillBelow::~FillBelow() {}

//subclass constructor fillbetween
FillBetween::FillBetween(Function &func1, Function &func2, float opacity, uint32_t red, uint32_t green, uint32_t blue) : Fill(opacity, red, green, blue), func1(&func1), func2(&func2){}
FillBetween::~FillBetween() {}

//setters for fill superclass
void Fill::set_type(string name) {
    this->type = name;
}
void Fill::set_opacity(float opacity) {
  this->opacity = opacity;
}
void Fill::set_r(uint32_t r) {
  this->r = r;
}
void Fill::set_g(uint32_t g) {
  this->g= g;
}
void Fill::set_b(uint32_t b) {
  this->b = b;
}

//getters for fill superclass
string Fill::get_type() {
  return this->type;
}
float Fill::get_opacity() {
  return this->opacity;
}
uint32_t Fill::get_r() {
  return this->r;
}
uint32_t Fill::get_g() {
  return this->g;
}
uint32_t Fill::get_b() {
  return this->b;
}
vector<Function*> Fill::get_funcs() { 
  return functions;
}

//public method, adds a function pointer to the vector of function pointers
void Fill::add_function(Function * func) {
  functions.push_back(func);
}