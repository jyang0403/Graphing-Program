#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <iostream>
#include "color.h"

class Image {
private:
  int m_width, m_height; //image dimensions
  Color *m_pixels; //array to store

  Image(const Image &);
  Image &operator=(const Image &);

public:
  Image(int width, int height);
  ~Image();

  //getter functions
  int get_width() const { return m_width; }
  int get_height() const { return m_height; }
  Color * get_color(int index);
  Color* get_pixels();

  //other member functions
  void write_png(std::ostream &out);
  void change_color(int index, uint32_t r, uint32_t g, uint32_t b);
};

#endif // IMAGE_H
