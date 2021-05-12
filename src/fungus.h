#ifndef FUNGUS_H
#define FUNGUS_H

#include "ofMain.h"
#include <numeric>
#include <vector>


namespace Fungus{

  //  [Brizo]
  //  ofPixels eh mais util para manipular pixels. Como so queremos exibir uma imagem, melhor
  //usar diretamente ofImage...
  //  E como a quantidade de texturas eh fixa, um array automático eh bem mais simples que um vector.
  static ofImage m_images[10];
  //static vector<ofPixels> m_images;

  static ofTexture m_texture;

  static void initImages(){

      m_texture.allocate(250,250,GL_RGBA);

      //  [Brizo]
      //
      //  Agora, se voce quer mesmo que m_images seja um vector, primeiro teria que popular esse vector,
      //chamando antes de cada m_images[i].allocate:
      //  ofPixels pixs0;
      //  m_images[0].push_back(pixs);
      //
      //  Como isto aqui eh so um namespace e nao uma classe, nao temos um destrutor onde limpar esse vector depois...
      //
      //  Eu acho bem mais simples o array automatico, entao o codigo abaixo fica todo inalterado:

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

  //  mudei de "drawFungus" para "draw"...
  static void draw(float xPosition, float yPosition, int radius, int minRadius, int maxRadius)
  {
    int imageIndex = std::ceil(ofMap(radius, minRadius, maxRadius, 0, 10));
    float factor = maxRadius / 2.5;
    //  Aqui tinhamos um problema: operacoes de memoria sendo executadas em grande quantidade (desenhar na tela
    //eh sempre em torno de uns 30 FPS...).
    //  O certo eh deixar carregado. Na hora de desenhar, simplemente chamar m_texture.draw. Eh exatamente o
    //que vamos fazer agora, ja que m_images agora ja sao as imagens carregadas.
    //  Assim, descomentamos essa linha loadData:
    m_texture.loadData(m_images[imageIndex]);
    m_texture.draw(xPosition - radius, yPosition - radius, radius * factor, radius * factor);
  }

}


#endif // FUNGUS_H
