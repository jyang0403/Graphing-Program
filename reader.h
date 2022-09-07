#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>
#include "plot.h"

using std::string;

class Reader {
private:
  // value semantics are prohibited
  Reader(const Reader &);
  Reader &operator=(const Reader &);

public:
  Reader();
  ~Reader();

  // read plot description of a certain input from given istream;
  // throw a PlotException if any errors are found
  void read_input(std::istream &in, Plot &plot);
  void read_plot(std::istream &in, Plot &plot);
  void read_function(std::istream &in, Plot &plot);
  void read_color(std::istream &in, Plot &plot);
  void read_fill(std::istream &in, Plot &plot, string str);
};

#endif // READER_H
