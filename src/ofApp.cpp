#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
  timeCount = 0;
  inc = 0.0005;
  yOff = 0;
  backgroundPixels.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
  ofSetCircleResolution(128);
  myTextures = Textures();
  myWorld = World(90, 15, myTextures.m_images, &myTextures.m_texture);
  generateBackground(); // to dynamic background comment this line


}

//--------------------------------------------------------------
void ofApp::update(){
// to dynamic background  uncommet those lines
// timeCount loop is used to control how many in how many frames a new background is generated.
//  if (timeCount == 10){
//      generateBackground();
//    }
//    timeCount++;
//    if (timeCount > 10) timeCount = 0;
// to generate a new background each frame use the line bellow
// generateBackground();
  myWorld.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(255);
  backgroundTexture.draw(0,0);
  myWorld.draw();
}

void ofApp::exit(){
  myWorld.closeOsc();
}

void ofApp::generateBackground(){
  int width = backgroundPixels.getWidth();
  int height = backgroundPixels.getHeight();
  for (int y = 0; y < height; y++){
      xOff = 0;
    for (int x = 0; x < width; x++){

          int index = x + y * width;
          backgroundPixels[index] = (ofNoise(xOff, yOff) * 70)+25;
          xOff += inc;
        }
    yOff += inc;
    }
  backgroundTexture.loadData(backgroundPixels);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
   myWorld.checkCollisionWithMouse(ofVec2f(x,y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
