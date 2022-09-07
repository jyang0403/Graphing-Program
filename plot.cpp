#include <cassert>
#include "plot.h"
#include "func.h"
#include "fill.h"
#include "exception.h"

using namespace std;

Plot::Plot() {}

Plot::~Plot() {
  //deleting vector of functions
  for(itr = functions.begin(); itr != functions.end(); ++itr) {
    delete *itr;
  }
  //deleting vector of fills
  for(itr_fill = fills.begin(); itr_fill != fills.end(); ++itr_fill) {
    delete *itr_fill;
  }
  //deleting bounds
  delete bounds;
  //remove all elements in fills vector container
  fills.clear();
  functions.clear();
}

//adds a function to the plot
void Plot::add_function(std::string &name, Function * func) {
  func->set_name(name);
  this->functions.push_back(func);
}
//finds a function by name and returns its pointer
Function* Plot::get_function(std::string &name) {
  for (Function* func : functions) {
    if (func->get_name() == name) {
      return func;
    }
  }
  throw PlotException("Error: function does not exist\n");
}

//getter and setter functions for bounds fields
double Plot::get_min_x() const { return bounds->get_min_x(); }
void Plot::set_min_x(double min) { bounds->set_min_x(min); }
double Plot::get_max_x() const { return bounds->get_max_x(); }
void Plot::set_max_x(double max) { bounds->set_max_x(max); }
double Plot::get_min_y() const { return bounds->get_min_y(); }
void Plot::set_min_y(double min) { bounds->set_min_y(min); }
double Plot::get_max_y() const { return bounds->get_max_y(); }
void Plot::set_max_y(double max) { bounds->set_max_y(max); }
void Plot::set_x_dimension(int x) { x_dimension = x; }
void Plot::set_y_dimension(int y) { y_dimension = y; }
int Plot::get_y_dimension() const { return y_dimension; }
int Plot::get_x_dimension() const { return x_dimension; }

//returns all functions
vector<Function*> Plot::get_functions() const {
  return functions;
}
//adds a fill
void Plot::add_to_fills(Fill * new_fill) {
  fills.push_back(new_fill);
}
//returns all fills
vector<Fill*> Plot::get_fills() const {
  return fills; 
} 
// returns index of a function specified by name in the plot
int Plot::get_func_index(string name) const {
  int index = 0;
  for (Function * func : this->functions) {
    if (func->get_name() == name) {
      return index;
    }
    index++;
  }
  throw PlotException("Error: cannot find index of function name \n");
}
