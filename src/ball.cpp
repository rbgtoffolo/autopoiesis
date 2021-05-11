#include "ball.h"
#include <iostream>
#include <numeric>
#include "constants.h"
#include <string>

Ball::Ball()
{

}

Ball::Ball(int id, int radius, int numPartials, int root, float minRoot, float maxRoot, ofVec2f position)
  : m_id(id),
    m_radius(radius),
    m_numPartials(numPartials),
    m_root(root),
    m_minRoot(minRoot), //necessary to scale color graduation
    m_maxRoot(maxRoot), //necessary to scale color graduation
    m_position(position)
{

  validateBall();
  calculateMass();
  for (int i = 0; i < numPartials; i++){
      float freq = m_root*(i+1);
      if (freq > 22050) freq = m_root;
      m_freqs.push_back(freq);
      m_amps.push_back(1.0f/(i+1));
    }
 // normalizeSumAmps();
  setColor();
  initAmpByRadius();
  m_velocity.set(0.5,0.5);
  m_acceleration.set(0,2);

  // call log function to show all parameters
  log("constructor");
}

// calculate Mass based on Radius
void Ball::calculateMass(){
  m_mass = ofMap(m_radius, MINRADIUS, MAXRADIUS, MINMASS, MAXMASS);
}

void Ball::update(){

  if ((m_position.x > ofGetWidth() - m_radius) || (m_position.x < m_radius)) {
      m_velocity.x *= -1;
    }
  if ((m_position.y > ofGetHeight() - m_radius) || (m_position.y < m_radius)) {
      m_velocity.y *= -1;
    }

  m_velocity += m_acceleration/m_mass;
  m_position += m_velocity;

}

void Ball::draw(vector<ofTexture> &texture){
  ofSetColor(m_color);
  int imageIndex = std::ceil(ofMap(m_radius, MINRADIUS, MAXRADIUS, 0, 10));
  float size = m_radius * (MAXRADIUS / 2.5);
  //texture[imageIndex].draw(m_position.x - m_radius, m_position - m_radius, size, size);
  //ofFill();
  // myFont.drawString(myString, position.x, position.y - radius - 2);
  //ofDrawCircle(m_position.x, m_position.y, m_radius);
  texture[imageIndex].draw(m_position.x - m_radius, m_position.y - m_radius, size, size);
}

float Ball::sumAmps(){
  return std::accumulate(m_amps.begin(), m_amps.end(),0);
}

void Ball::setColor(){
  float tempHue = ofMap(m_root, m_minRoot, m_maxRoot, 200, 0);
  //float tempSat = ofMap(sumAmps(), 0, 1, 0, 200 );
  float tempSat = 255;
  float tempBright = tempSat;
  float tempAlpha = 255;
  m_color = ofColor::fromHsb(tempHue, tempSat, tempBright, tempAlpha);
}

void Ball::validateBall(){
  if (m_radius < MINRADIUS) m_radius = MINRADIUS;
  if (m_radius > MAXRADIUS) m_radius = MAXRADIUS;
  if (m_minRoot < 20.0f) m_minRoot = 20.0f;
  if (m_minRoot > 20000.0f) m_minRoot = 20000.0f;
  if (m_maxRoot < 20.0f) m_minRoot = 20.0f;
  if (m_maxRoot > 20000.0f) m_minRoot = 20000.0f;
  if (m_minRoot > m_maxRoot) {
      float temp = m_minRoot;
      m_minRoot = m_maxRoot;
      m_maxRoot = temp;
    }
}

void Ball::applyForce(ofVec2f force){
  m_acceleration += (force/m_mass);
}

void Ball::decreaseRadius(int factor){
  int oldRadius = m_radius;
  m_radius -= factor;
  if (m_radius < MINRADIUS) m_radius = MINRADIUS;
  scaleByRadius(oldRadius, m_radius);
  calculateMass();
  log("decrease r");
}

void Ball::increaseRadius(int factor){
  int oldRadius = m_radius;
  m_radius += factor;
  if (m_radius > MAXRADIUS) m_radius = MAXRADIUS;
  scaleByRadius(oldRadius, m_radius);
  calculateMass();
  log ("increase r");
}


void Ball::scaleByRadius(int oldRadius, int newRadius){
//  float finalFactor = ofMap(m_radius, MINRADIUS, MAXRADIUS, 0.01f, 1.0f);
//  float inicialFactor = m_amps[0];
//  float scale = finalFactor/inicialFactor;
//  for (int i = 0; i < m_numPartials; i++){
//      m_amps[i] *= scale;
////      if (m_amps[i] == 0) m_amps[i] = 0.00001;
//    }
  for (int i = 0; i < m_numPartials; i++){
      m_amps[i] = (m_amps[i]*newRadius)/oldRadius;
    }
    setColor();
}

void Ball::initAmpByRadius(){
  float finalFactor = ofMap(m_radius, MINRADIUS, MAXRADIUS, 0.01f, 1.0f);
  float inicialFactor = m_amps[0];
  float scale = finalFactor/inicialFactor;
  for (int i = 0; i < m_numPartials; i++){
      m_amps[i] *= scale;
//      if (m_amps[i] == 0) m_amps[i] = 0.00001;
    }
    setColor();
}

void Ball::log(string myString){
  std::clog << "[" << myString << "]";
  std::clog << " Id: " << m_id ;
  std::clog << " - Radius: " << m_radius;
  std::clog << " - Mass: " << m_mass;
  std::clog << " - Amps: ";
  for (int i = 0; i < m_numPartials; i++){
      std::clog << m_amps[i] << " ";
    }
  std::clog << " - Freqs: ";
  for (int i = 0; i < m_numPartials; i++){
      std::clog << m_freqs[i] << " ";
    }
  std::clog << " - Vel.x " << m_velocity.x << " Vel.y " << m_velocity.y;
  std::clog << std::endl;
}



