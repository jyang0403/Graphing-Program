#include "bounds.h"

Bounds::Bounds() {
}
Bounds::~Bounds() {
}
//getter and setter functions for dimensions of plot/image
double Bounds::get_min_x() { return x_min; }
double Bounds::get_max_x() { return x_max; }
double Bounds::get_min_y() { return y_min; }
double Bounds::get_max_y() { return y_max; }
void Bounds::set_min_x(double min) { this->x_min = min; }
void Bounds::set_min_y(double min) { this->y_min = min; }
void Bounds::set_max_x(double max) { this->x_max = max; }
void Bounds::set_max_y(double max) { this->y_max = max; }