#include "textures.h"

Textures::Textures()
{
  m_texture.allocate(250, 250, GL_RGBA);
  for (int i = 0; i < 11; i++){
      std::string myPath = "t0" + to_string(i) + ".png";
      m_images[i].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[i].clear();
      ofLoadImage(m_images[i], myPath);
    }
}

//void Textures::draw(float xPosition, float yPosition, int radius, int minRadius, int maxRadius){
//  int imageIndex = std::ceil(ofMap(radius, minRadius, maxRadius, 0, 10));
//  float factor = maxRadius / 2.5;
//  m_texture.loadData(m_images[imageIndex]);
//  m_texture.draw(xPosition - radius, yPosition - radius, radius * factor, radius * factor);
//}
