#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include "func.h"
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "expr_parser.h"
#include "fill.h"

using std::string;
using std::vector;
using std::stringstream;

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::read_input(std::istream &in, Plot &plot) {
  string str; //read directive
  while (in >> str) {
    if (str == "Plot") {
      read_plot(in, plot);
    }
    else if (str == "Function") {
      read_function(in,plot);
    }
    else if (str == "Color") {
      read_color(in,plot);
    }
    else if (str.substr(0,4) == "Fill") {
      read_fill(in,plot,str);
    }
    else {
      throw PlotException("Error: invalid directive\n");
    }
  }
}
void Reader::read_plot(std::istream &in, Plot &plot) {
  vector<double> coords;
  string str;
  double next;
  getline(in, str);
  stringstream ss(str);
  while (ss >> next) {
    coords.push_back(next); //store numeric values in a vector
  }
  //check for errors: bounds, # inputs, etc.
  if (coords.size() != 6) {
    throw PlotException("Error: Invalid number of arguments\n");
  }
  if (coords[4] <= 0 || coords[5] <= 0) {
    throw PlotException("Error: Invalid width or height dimension\n");
  }
  if (coords[0] >= coords[2]) {
    // x min greater than x max
    throw PlotException("Error: xmin >= xmax\n");
  }
  if (coords[1] >= coords[3]) {
    // y min greater than y max
    throw PlotException("Error: ymin >= ymax\n");
  }
  plot.set_min_x(coords[0]);
  plot.set_min_y(coords[1]);
  plot.set_max_x(coords[2]);
  plot.set_max_y(coords[3]);
  plot.set_x_dimension(coords[4]);
  plot.set_y_dimension(coords[5]);
}
void Reader::read_function(std::istream &in, Plot &plot) {
  // store each Function within a map of function names and their respective values within plot
  string function_name;
  in >> function_name;
  // parse function and add it to the plot in order
  ExprParser * parse = new ExprParser();
  Expr * expression = parse->parse(in);
  Function * new_func = new Function(function_name, expression);
  plot.add_function(function_name, new_func);
  delete parse;
}
void Reader::read_color(std::istream &in, Plot &plot) {
  string funcName;
  //extract function name
  in >> funcName;
  vector<int> color_test;
  vector<uint32_t> color;
  string str;
  getline(in, str);
  stringstream ss(str);
  int next;
  while(ss >> next) {
    color_test.push_back(next);
  }
  //check for valid number of inputs for color values
  if (color_test.size() != 3) {
    throw PlotException("Error: Incorrect number of inputs\n");
  }
  //check for valid color value
  for (int i : color_test) {
    if (i < 0 || i > 255) {
      throw PlotException("Error: Color value is not within appropriate bounds\n");
    }
    color.push_back((uint32_t) i);
  }
  //setting colors
  //creating pointer to function of given name
  if (plot.get_function(funcName)->color_check() == 0) {
    plot.get_function(funcName)->set_color(color[0], color[1], color[2]);
    plot.get_function(funcName)->set_color_check(true);
  }
  else {
    throw PlotException("Error: function already has existing color directive\n");
  }
}

void Reader::read_fill(std::istream &in, Plot &plot, string str) {
  string func1_name, func2_name;
  float opacity;
  vector<double> color_test;
  vector<uint32_t> colors;
  uint32_t color;
  string string2;
  getline(in,string2);
  stringstream ss(string2);
  //read function name(s) if possible
  if (str == "FillBetween") {
    if (!(ss >> func1_name >> func2_name)) {
      throw PlotException("Error: Incorrect number of functions for FillBetween\n");
    }
  }
  else {
    if (!(ss >> func1_name)) {
      throw PlotException("Error: Incorrect input for function name\n");
    }
  }
  
  //read opacity and check whether out of bounds
  if(!(ss >> opacity) || opacity < 0.0 || opacity > 1.0)  {
    throw PlotException("Error: Incorrect value for opacity\n");
  }

  //read r g b and check number of inputs and whether any are out of bounds
  while (ss >> color) {
    color_test.push_back(color);
  }
  if (color_test.size() != 3) {
    throw PlotException("Error: Incorrect number of inputs\n");
  }
  for (int i : color_test) {
    if (i < 0 || i > 255) {
      throw PlotException("Error: Color value is not within appropriate bounds\n");
    }
    colors.push_back((uint32_t) i);
  }

//set pointer to point to a fill subclass object, setting its corresponding function(s), colors, type, and opacity in order of appearance
  // add ONE function for above and below
  if (str == "FillAbove") {
    FillAbove * new_fill = new FillAbove(*(plot.get_function(func1_name)), opacity, colors[0], colors[1], colors[2]);
    new_fill->add_function((plot.get_function(func1_name)));
    new_fill->set_type("above");
    plot.add_to_fills(new_fill);
  }
  else if (str == "FillBelow") {
    FillBelow * new_fill = new FillBelow(*(plot.get_function(func1_name)), opacity, colors[0], colors[1], colors[2]); 
    new_fill->add_function((plot.get_function(func1_name)));
    new_fill->set_type("below");
    plot.add_to_fills(new_fill);
  }
  else if (str == "FillBetween") {
    //add TWO functions to the fill if fillbetween
    FillBetween * new_fill = new FillBetween(*(plot.get_function(func1_name)), *(plot.get_function(func2_name)), opacity, colors[0], colors[1], colors[2]);
    new_fill->add_function((plot.get_function(func1_name)));
    new_fill->add_function((plot.get_function(func2_name)));
    new_fill->set_type("between");
    plot.add_to_fills(new_fill);
  }
}
