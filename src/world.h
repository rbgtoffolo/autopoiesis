#ifndef WORLD_H
#define WORLD_H

#include "ofMain.h"
#include "ball.h"
#include "ofxOsc.h"

class World
{
public:
  World();
  World(int numOfBalls, int numPartials);
  void update();
  void draw();
  void closeOsc();



private:

  int m_numBalls;
  int m_numPartials;
  vector<ofTexture> m_textures;

  vector<Ball> m_balls;
  void checkCollision();
  bool collision(Ball &one, Ball &other);
  void repulsion(Ball &one, Ball &other);
  int affinity(Ball &one, Ball &other);
  void attraction(Ball &one, Ball &other, int &affinity);
  ofxOscSender m_sender;
  void scaleAllAmps();
  void sendOscAmps(Ball &ball);
  void initAllSynths();
  void updatePan(Ball &ball);
  void initTextures();

};

#endif // WORLD_H
