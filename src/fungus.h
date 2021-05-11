#ifndef FUNGUS_H
#define FUNGUS_H

#include "ofMain.h"
#include <numeric>
#include <vector>


namespace Fungus{

  static vector<ofPixels> m_images;
  static ofTexture m_texture;

  static void initImages(){

      m_texture.allocate(250,250,GL_RGBA);

      m_images[0].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[0].clear();
      ofLoadImage(m_images[0], "t00.png");

      m_images[1].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[1].clear();
      ofLoadImage(m_images[1], "t01.png");

      m_images[2].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[2].clear();
      ofLoadImage(m_images[2], "t02.png");

      m_images[3].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[3].clear();
      ofLoadImage(m_images[3], "t03.png");

      m_images[4].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[4].clear();
      ofLoadImage(m_images[4], "t04.png");

      m_images[5].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[5].clear();
      ofLoadImage(m_images[5], "t05.png");

      m_images[6].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[6].clear();
      ofLoadImage(m_images[6], "t06.png");

      m_images[7].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[7].clear();
      ofLoadImage(m_images[7], "t07.png");

      m_images[8].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[8].clear();
      ofLoadImage(m_images[8], "t08.png");

      m_images[9].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[9].clear();
      ofLoadImage(m_images[9], "t09.png");

      m_images[10].allocate(250,250,OF_IMAGE_COLOR_ALPHA);
      m_images[10].clear();
      ofLoadImage(m_images[10], "t010.png");

}


  static void drawFungus(float xPosition, float yPosition, int radius, int minRadius, int maxRadius){
    int imageIndex = std::ceil(ofMap(radius, minRadius, maxRadius, 0, 10));
    float factor = maxRadius / 2.5;
    m_texture.loadData(m_images[imageIndex]);
    m_texture.draw(xPosition - radius, yPosition - radius, radius * factor, radius * factor);
  }

}


#endif // FUNGUS_H
