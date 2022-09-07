#include "pnglite.h"
#include "exception.h"
#include <cassert>
#include "image.h"

namespace {

struct InitializePnglite {
  InitializePnglite() {
    ::png_init(0, 0);
  }
};

InitializePnglite init_pnglite;

unsigned ostream_png_write_callback(void* input, size_t size, size_t numel, void* user_pointer) {
  std::ostream &out = *(reinterpret_cast<std::ostream *>(user_pointer));
  out.write(reinterpret_cast<const char *>(input), size * numel);
  if (!out.good()) {
    throw PlotException("Error writing output data");
  }
  return numel;
}

} // end anonymous namespace

Image::Image(int width, int height)
  : m_width(width)
  , m_height(height)
  , m_pixels(new Color[width * height]) {
    //set default color of each pixel to black
    for (int i = 0; i < m_width * m_height; i++) {
      m_pixels[i].r = 0;
      m_pixels[i].g = 0;
      m_pixels[i].b = 0;
    };
}

Image::~Image() {
  delete[] m_pixels;
}

Color * Image::get_color(int index) {
  // check if out of bounds
  if (index < 0 || index >= m_width * m_height) {
    throw PlotException("Error: Invalid index for get_color");
  }
  return &m_pixels[index];
}
// changes color of given pixel
void Image::change_color(int index, uint32_t red, uint32_t green, uint32_t blue) {
  assert(red < 256);
  assert(green < 256);
  assert(blue < 256);
  m_pixels[index].r = red;
  m_pixels[index].g = green;
  m_pixels[index].b = blue;
}

//returns array of pixels
Color* Image::get_pixels() {
  return m_pixels;
}

void Image::write_png(std::ostream &out)
{
  // Set up png_t object for output
  png_t png;
  int rc;

  rc = png_open_write(&png, ostream_png_write_callback, static_cast<void*>(&out));
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error opening PNG output");
  }

  // get pixel data as unsigned char *
  const unsigned char *pixels_raw_const = reinterpret_cast<const unsigned char *>(get_pixels());
  unsigned char *pixels_raw = const_cast<unsigned char *>(pixels_raw_const);

  // Write PNG data
  rc = png_set_data(&png, unsigned(m_width), unsigned(m_height), 8, PNG_TRUECOLOR,
                   pixels_raw);
  if (rc != PNG_NO_ERROR) {
    throw PlotException("Error converting writing image data as PNG");
  }
}