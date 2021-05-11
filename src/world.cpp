#include "world.h"
#include "constants.h"
#include <cmath>

World::World(){}

World::World(int numBalls, int numPartials)
  : m_numBalls(numBalls),
    m_numPartials(numPartials)
{
  initTextures();
  for (int i = 0; i< m_numBalls; i++){
      Ball tempBall;
      tempBall = Ball(i,
                      (int)ofRandom(MINRADIUS,MAXRADIUS),
                      m_numPartials,
                      (int)ofRandom(BASEROOT, TOPROOT),
                      MINROOT,
                      MAXROOT,
                      ofVec2f(ofRandom(50,ofGetWidth()), ofRandom(50,ofGetHeight()))
                      );
      tempBall.setVelocity(ofVec2f(ofRandom(-5, 5), ofRandom(-5,5)));
      tempBall.setAcceleration(ofVec2f(0,0));
      m_balls.push_back(tempBall);
    }

  scaleAllAmps();

  // setup OSC Sender and setup Massage passing constructor infos
  m_sender.setup(HOST, SCPORT);
  ofxOscMessage m;
  m.setAddress("/of/setup");
  m.addIntArg(m_numBalls);
  m.addIntArg(m_numPartials);
  m_sender.sendMessage(m);

  initAllSynths(); // start all synths with freqs and amps in SC
}

void World::initTextures(){
  m_textures[0].allocate(250,250,GL_RGBA);
  m_textures[0].clear();
  ofLoadImage(m_textures[0], "t00.png");

  m_textures[1].allocate(250,250,GL_RGBA);
  m_textures[1].clear();
  ofLoadImage(m_textures[1], "t01.png");

  m_textures[2].allocate(250,250,GL_RGBA);
  m_textures[2].clear();
  ofLoadImage(m_textures[2], "t02.png");

  m_textures[3].allocate(250,250,GL_RGBA);
  m_textures[3].clear();
  ofLoadImage(m_textures[3], "t03.png");

  m_textures[4].allocate(250,250,GL_RGBA);
  m_textures[4].clear();
  ofLoadImage(m_textures[4], "t04.png");

  m_textures[5].allocate(250,250,GL_RGBA);
  m_textures[5].clear();
  ofLoadImage(m_textures[5], "t05.png");

  m_textures[6].allocate(250,250,GL_RGBA);
  m_textures[6].clear();
  ofLoadImage(m_textures[6], "t06.png");

  m_textures[7].allocate(250,250,GL_RGBA);
  m_textures[7].clear();
  ofLoadImage(m_textures[7], "t07.png");

  m_textures[8].allocate(250,250,GL_RGBA);
  m_textures[8].clear();
  ofLoadImage(m_textures[8], "t08.png");

  m_textures[9].allocate(250,250,GL_RGBA);
  m_textures[9].clear();
  ofLoadImage(m_textures[9], "t09.png");

  m_textures[10].allocate(250,250,GL_RGBA);
  m_textures[10].clear();
  ofLoadImage(m_textures[10], "t010.png");

}

void World::update(){

  checkCollision();
  for (auto &ball : m_balls){
      ball.update();
    }
}

void World::draw(){

  for (auto &ball : m_balls){
      ball.draw(m_textures);
      updatePan(ball);
    }
}

void World::checkCollision(){

  for (int i = 0; i < m_numBalls - 1; i++){
      for (int j = i + 1; j < m_numBalls; j++){
          Ball &one = m_balls[i];
          Ball &other = m_balls[j];
          if (collision(one, other))
            {
              int tempAffinity = affinity(one, other);
              if(tempAffinity == 0){
                  repulsion(one, other);
                }
              if(tempAffinity >= 1){
                  attraction(one, other, tempAffinity);
                }
            }
        }
    }
}

bool World::collision(Ball &one, Ball &other){

  float dist = one.position().distance(other.position());
  float sumRadius = one.radius() + other.radius();
  if (dist <= sumRadius) {return true;}
  else {return false;}
}

void World::repulsion(Ball &one, Ball &other){

  float newMass, diff, angle, newX, newY, newVelocityX, newVelocityY, fy21, sign;

  newMass = other.mass()/one.mass();
  newX = other.xPosition() - one.xPosition();
  newY = other.yPosition() - one.yPosition();
  newVelocityX = other.xVelocity() - one.xVelocity();
  newVelocityY = other.yVelocity() - one.yVelocity();

  if ((newVelocityX*newX + newVelocityY*newY)>=0) return;

  fy21=fabs(newY);
  if (fabs(newX)>fy21){
      if (newX>0){sign = -1;} else {sign=1;}
      newX=fy21*sign;
    }

  angle = newY/newX;
  diff = -2 * (newVelocityX + angle * newVelocityY)/((1+angle * angle)*(1+ newMass));
  other.setXVelocity(other.xVelocity() + diff);
  other.setYVelocity(other.yVelocity() + angle * diff);

  one.setXVelocity(one.xVelocity() - newMass * diff);
  one.setYVelocity(one.yVelocity() -angle * newMass * diff);

  if (one.xVelocity() < 0.001 && one.yVelocity() < 0.001) one.setVelocity(ofVec2f {ofRandom(-5.0f,5.0f), ofRandom(-5.0f,5.0f)});
  if (other.xVelocity() < 0.001 && other.yVelocity() < 0.001) other.setVelocity(ofVec2f {ofRandom(-5.0f,5.0f), ofRandom(-5.0f,5.0f)});


  one.decreaseRadius(std::ceil(other.radius()/one.radius()));
  other.decreaseRadius(std::ceil(one.radius()/other.radius()));

  sendOscAmps(one);
  sendOscAmps(other);
}

void World::attraction(Ball &one, Ball &other, int &affinity){

  ofVec2f oneVelocity = one.velocity();
  ofVec2f otherVelocity = other.velocity();
  one.setVelocity(otherVelocity);
  other.setVelocity(oneVelocity);
  one.increaseRadius(1);
  other.increaseRadius(1);
  one.decreaseVelocity(affinity+1);
  other.decreaseVelocity(affinity+1);
  sendOscAmps(one);
  sendOscAmps(other);
}

int World::affinity(Ball &one, Ball &other){

  int affinity = 0;
  for (int i = 0; i< m_numPartials; i++){
      for (int j = 0; j < m_numPartials; j++){
          if (one.freq(i) == other.freq(j)) affinity++;
        }
    }
  return affinity;
}


void World::scaleAllAmps(){

  for (int i = 0; i < m_numBalls; i++){
      for (int j = 0; j < m_numPartials; j++){
          m_balls[i].setAmplitude(j, m_balls[i].amp(j)/m_numBalls);
        }
      m_balls[i].log("scaleAllAmps");
    }
}

void World::sendOscAmps(Ball &ball){

  ofxOscMessage m;
  m.setAddress("/of/updateAmps");
  m.addIntArg(ball.id());
  for (int i = 0; i < m_numPartials; i++){
      m.addFloatArg(ball.amp(i));
    }
  m_sender.sendMessage(m);
}


void World::initAllSynths(){

  for (int i = 0; i < m_numBalls; i++){
      ofxOscMessage m;
      m.setAddress("/of/setSynths");
      m.addIntArg(m_balls[i].id());
      for (int j = 0; j< m_numPartials; j++){
          m.addFloatArg(m_balls[i].freq(j));
          m.addFloatArg(m_balls[i].amp(j));
        }
      m_sender.sendMessage(m);
    }
}

void World::closeOsc(){
  ofxOscMessage m;
  m.setAddress("/of/closeOsc");
  m_sender.sendMessage(m);

}

void World::updatePan(Ball &ball){
  float pan = ofMap(ball.xPosition(), 0, ofGetWidth(), -1.0f, 1.0f);
  ofxOscMessage m;
  m.setAddress("/of/updatePan");
  m.addIntArg(ball.id());
  m.addFloatArg(pan);
  m_sender.sendMessage(m);
}


