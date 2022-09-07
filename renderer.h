#ifndef RENDERER_H
#define RENDERER_H

#include "plot.h"
#include "image.h"

class Renderer {
private:

  const Plot &m_plot;
  Image *m_img;

  Renderer(const Renderer &);
  Renderer &operator=(const Renderer &);

public:
  Renderer(const Plot &plot);
  ~Renderer();
  Image *render();
private:
};

#endif // RENDERER_H
