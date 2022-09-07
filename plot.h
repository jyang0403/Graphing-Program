#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "image.h"
#include "func.h"
#include "fill.h"

using namespace std;

class Plot {
private:

  vector<Function*> functions;
  vector<Function*>::iterator itr;
  Bounds * bounds = new Bounds();
  int x_dimension;
  int y_dimension;

  vector<Fill*> fills; //a vector of Fill objects that take function(s) and stores data of regions to be filled
  vector<Fill*>::iterator itr_fill; 

  Plot(const Plot &);
  Plot &operator=(const Plot &);

public:
  Plot();
  ~Plot();
  //getter and setter functions
  double get_min_x() const;
  void set_min_x(double min);
  double get_max_x() const;
  void set_max_x(double max);
  double get_min_y() const;
  void set_min_y(double min);
  double get_max_y() const;
  void set_max_y(double max);
  void set_x_dimension(int x);
  int get_x_dimension() const;
  void set_y_dimension(int y);
  int get_y_dimension() const;
  //adds a function to a fill
  void add_function(std::string &name, Function * func);
  //returns a function with the given name
  Function* get_function(std::string &name);
  // returns all functions of a fill
  std::vector<Function*> get_functions() const;
  //adds a fill to existing fills
  void add_to_fill(vector<Fill> fills, Fill new_fill);
  vector<Fill*> get_fills() const;
  //gets index of a function in the plot
  int get_func_index(string name) const;
  //adds a fill
  void add_to_fills(Fill * new_fill);
};

#endif // PLOT_H

