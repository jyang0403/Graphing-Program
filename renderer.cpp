#include <cstdint>
#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <stdint.h>
#include "exception.h"
#include "renderer.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT
using std::uint8_t;
using std::vector;

Renderer::Renderer(const Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {
}

Renderer::~Renderer() {}

//checks if a given index in the image is within the fillbelow area
bool inside_fillbelow(int index, int width, vector<double> coordinates) {
  //compare a pixel index to relative y-value of a certain column
  if (index > coordinates[index % width]) {
    return true;
  }
  return false;
}

//checks if a given index in the image is within the fillabove area
bool inside_fillabove(int index, int width, vector<double> coordinates) {
  //compare a pixel index to relative y-value of a certain column
  if (index < coordinates[index % width]) {
    return true;
  }
  return false;
}

//checks if a given index in the image is within the fillbetween area
bool inside_fillbetween(int index, int width, vector<double> coordinates1, vector<double> coordinates2) {
  //compare a pixel index to two relative y-values of a certain column
  if ((index > coordinates1[index % width] && index < coordinates2[index % width]) || (index < coordinates1[index % width] && index > coordinates2[index % width])) {
    return true;
  }
  return false;
}

Image *Renderer::render() {
  double width = m_plot.get_x_dimension();
  double height = m_plot.get_y_dimension();
  double max_x = m_plot.get_max_x();
  double min_x = m_plot.get_min_x();
  // the unique_ptr will take care of deleting the Image object if an exception was thrown
  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();
  // includes every y-value for all functions
  vector<vector<double>> coordinates;
  // for each function, calculate each x's respective y value then convert that value to fit the plot's orientation/dimensions
  for (Function * func : m_plot.get_functions()) {
    vector<double> new_coord;
    // x = 0 line
    double center_row = (height * width) / 2;
    double y_value;
    int index = 0;
    //converts y dimension to fit a row index
    double y_scalar = height / (fabs(m_plot.get_max_y() - m_plot.get_min_y()));
    //convert x to its relative index to the plot
    for (double i = min_x; i <= max_x; i += (fabs(max_x) + fabs(min_x)) / width) {
      //evaluate and multiply y-value by scalar
      y_value = func->get_expr()->eval(i);
      y_value *= y_scalar;
      //adjust for rounding/index difference between if y is positive vs nonpositive
      if (y_value >= 0) {
        y_value++;
      }
      //index in terms of image dimensions/orientation and round y_value by casting
      new_coord.push_back(center_row + index - (((int) y_value) * width));
      index++;
    }
    //add vector to set of all y-coordinates
    coordinates.push_back(new_coord);
  }
  //calculate and draw fills
  for (Fill * fill : m_plot.get_fills()) {
      for (int i = 0; i < height * width; i++) {
        // overloaded depending on whether it is fillabove or below
        if (fill->get_type() == "above") {
          int current_func = m_plot.get_func_index(fill->get_funcs()[0]->get_name());
          if (inside_fillabove(i, width, coordinates[current_func])) {
            //calculate new opacity and change color if inside fill
            double red_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].r + fill->get_opacity() * fill->get_r();
            double green_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].g + fill->get_opacity() * fill->get_g();
            double blue_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].b + fill->get_opacity() * fill->get_b();
            m_img->change_color(i, red_opacity, green_opacity, blue_opacity);
          }
        }
        else if (fill->get_type() == "below") {
          int current_func = m_plot.get_func_index(fill->get_funcs()[0]->get_name());
          //calculate new opacity and change color if inside fill
          if (inside_fillbelow(i, width, coordinates[current_func])) {
            double red_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].r + fill->get_opacity() * fill->get_r();
            double green_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].g + fill->get_opacity() * fill->get_g();
            double blue_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].b + fill->get_opacity() * fill->get_b();
            m_img->change_color(i, red_opacity, green_opacity, blue_opacity);
          }
        }
        else {
          //find respective indices of the two functions in a fillbetween, then retrieve those sets from coordinates
          int func1_index = m_plot.get_func_index(fill->get_funcs()[0]->get_name());
          int func2_index = m_plot.get_func_index(fill->get_funcs()[1]->get_name());
          //calculate new opacity and change color if within fill
          if (inside_fillbetween(i, width, coordinates[func1_index], coordinates[func2_index])) {
            double red_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].r + fill->get_opacity() * fill->get_r();
            double green_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].g + fill->get_opacity() * fill->get_g();
            double blue_opacity = (1 - fill->get_opacity()) * m_img->get_pixels()[i].b + fill->get_opacity() * fill->get_b();
            m_img->change_color(i, red_opacity, green_opacity, blue_opacity);
          }
        }
      }
  }
  //draw function lines
  int current_func = 0;
  for (Function * func : m_plot.get_functions()) {
    vector<double> current = coordinates[current_func];
    //change one pixel for each column
    for (int i = 0; i < width; i++) {
      int pixel_index = current[i];
      m_img->change_color(pixel_index, func->get_r(), func->get_g(), func->get_b());
      // change pixel to the left if possible
      if (i > 0) {
        m_img->change_color(pixel_index - 1, func->get_r(), func->get_g(), func->get_b());
      }
      // change pixel to the right
      if (i < width - 1) {
        m_img->change_color(pixel_index + 1, func->get_r(), func->get_g(), func->get_b());
      }
      // change pixel above
      if (pixel_index > width) {
        m_img->change_color(pixel_index - width, func->get_r(), func->get_g(), func->get_b());
      }
      // change pixel below
      if (pixel_index < height * (width - 1)) {
        m_img->change_color(pixel_index + width, func->get_r(), func->get_g(), func->get_b());
      }
    }
    // move on to the next function's coordinates
    current_func++;
  }
  return img.release();
}