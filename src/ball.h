#ifndef BALL_H
#define BALL_H

#include "ofMain.h"
#include "constants.h"
#include <string>
#include "textures.h"

class Ball
{
public:
  Ball();
  Ball(int id, int radius, int numPartials, int root, float minRoot, float maxRoot, ofVec2f position, ofPixels p_imagesPtr[], ofTexture *p_texturePtr);
  void update();
  void setRadius(int radius){ m_radius = radius;};
  void setPosition(ofVec2f position){ m_position = position;};
  void setVelocity(ofVec2f velocity){m_velocity = velocity;}
  void setXVelocity(float xVelocity) {m_velocity.x = xVelocity;};
  void setYVelocity(float yVelocity) {m_velocity.y = yVelocity;};
  void setAcceleration(ofVec2f acceleration){m_acceleration = acceleration;};
  void applyForce(ofVec2f force);
  ofVec2f position() const {return m_position;};
  float xPosition() const {return m_position.x;};
  float yPosition() const {return m_position.y;};
  float xVelocity() const {return m_velocity.x;};
  float yVelocity() const {return m_velocity.y;};
  float radius() const {return m_radius;};

  ofVec2f velocity() const {return m_velocity;};
  float mass() const {return m_mass;};
  void setColor();
  void draw();
  int freq(int index) const {return m_freqs[index];};
  void decreaseRadius(int factor);
  void increaseRadius(int factor);
  void decreaseVelocity(float factor){m_velocity /= factor;};
  float amp(int index) const { return m_amps[index];};
  void setAmplitude(int index, float value){m_amps[index] = value;};
  int id() const {return m_id;};

private:
  int m_id;
  int m_radius;
  int m_numPartials;
  int m_root;
  float m_minRoot;
  float m_maxRoot;
  ofVec2f m_position;
  ofPixels *m_imagesPtr;
  ofTexture *m_texturePtr;


  ofVec2f m_velocity;
  ofVec2f m_acceleration;
  float m_mass;

  ofColor m_color;
  vector<float> m_amps;
  vector<float> m_freqs;

public:

  float sumAmps();
  void validateBall();
  void calculateMass(); // calculate mass based on radius
  void scaleByRadius(int oldRadius, int newRadius);
  void initAmpByRadius();
  void loadImages();

  void log(std::string callFunction);

};





#endif // BALL_H
