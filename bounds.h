#ifndef BOUNDS_H
#define BOUNDS_H

class Bounds {
private:
  double y_min;
  double y_max;
  double x_min;
  double x_max;
public:
  Bounds();
  ~Bounds();
  //getter and setters. stores a plot's dimension data
  double get_min_x();
  void set_min_x(double min);
  double get_max_x();
  void set_max_x(double max);
  double get_min_y();
  void set_min_y(double min);
  double get_max_y();
  void set_max_y(double max);
};

#endif // BOUNDS_H
