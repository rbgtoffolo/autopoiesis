#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
  ofSetBackgroundColor(144);
  ofSetCircleResolution(128);
  myTextures = Textures();
  myWorld = World(10, 15, myTextures.m_images, &myTextures.m_texture);


}

//--------------------------------------------------------------
void ofApp::update(){
  myWorld.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
  myWorld.draw();
}

void ofApp::exit(){
  myWorld.closeOsc();
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
