#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"
#include "func.h"
#include <vector>

using std::vector;
using std::string;

class Fill {
private:
  float opacity;
  string type;
  uint32_t r;
  uint32_t g;
  uint32_t b;
  vector<Function*> functions;

public:
  Fill();
  Fill(float opacity, uint32_t red, uint32_t green, uint32_t blue);
  ~Fill();

  //setters for fill superclass
  void set_opacity(float opacity);
  void set_r(uint32_t r);
  void set_g(uint32_t g);
  void set_b(uint32_t b);
  void set_type(string type);
  //getters for fill superclass
  string get_type();
  float get_opacity();
  uint32_t get_r(); 
  uint32_t get_g();
  uint32_t get_b();
  //return vector of all functions in a fill (either of size one or two)
  vector<Function*> get_funcs();
  //adds function to fill
  void add_function(Function * func);
};

//for FillAbove command
class FillAbove : public Fill{
private:
  Function * func; 
public:
  FillAbove(Function &func, float opacity, uint32_t red, uint32_t green, uint32_t blue);
  ~FillAbove();
};

//for FillBelow command
class FillBelow : public Fill{
private:
  Function * func;
public:
  FillBelow(Function &func, float opacity, uint32_t red, uint32_t green, uint32_t blue);
  ~FillBelow();
};

//for FillBetween command
class FillBetween : public Fill{
private:
  Function * func1;
  Function * func2;
public:
  FillBetween(Function &func1, Function &func2, float opacity, uint32_t red, uint32_t green, uint32_t blue);
  ~FillBetween();
};

#endif // FILL_H