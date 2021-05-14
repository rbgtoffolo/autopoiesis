#ifndef TEXTURES_H
#define TEXTURES_H

#include "ofMain.h"
#include "constants.h"

class Textures
{
public:
  Textures();

  ofPixels m_images[TEXTUREFILES];
  ofTexture m_texture;

};

#endif // TEXTURES_H
