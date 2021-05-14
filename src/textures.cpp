#include "textures.h"

Textures::Textures()
{
  m_texture.allocate(250, 250, GL_RGBA);
  for (int i = 0; i < TEXTUREFILES; i++){
      std::string myPath = "t0" + to_string(i) + ".png";
      m_images[i].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[i].clear();
      ofLoadImage(m_images[i], myPath);
    }
}

