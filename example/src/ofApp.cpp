#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  vidGrabber.setDeviceID(0);
  vidGrabber.setDesiredFrameRate(60);
  vidGrabber.initGrabber(1920, 1080);

  chilitags.init();
}

//--------------------------------------------------------------
void ofApp::update(){

  vidGrabber.update();
  if ( !vidGrabber.isFrameNew() )
    return;
  rgb = vidGrabber.getPixels();
  //ofxCv::flip(rgb, rgb, 1); //some cameras need flipping
  texRGB.loadData(rgb);

  chilitags.update(rgb);
}

//--------------------------------------------------------------
void ofApp::draw(){

  float w = ofGetWidth();
  float h = ofGetHeight();

  texRGB.draw(0, 0, w, h);

  chilitags.render(0, 0, w, h);
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
