#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  vector <ofxKinectV2::KinectDeviceInfo> deviceList = kinect.getDeviceList();
  if (deviceList.empty())
  {
    ofLogError("kinect device list is empty");
    ofExit();
  }
  kinect.open(deviceList[0].serial);

  chilitags.init();
}

//--------------------------------------------------------------
void ofApp::update(){

  kinect.update();
  if ( !kinect.isFrameNew() )
    return;
  rgb = kinect.getRgbPixels();
  ofxCv::flip(rgb, rgb, 1);
  texRGB.loadData(rgb);
  texDepth.loadData(kinect.getDepthPixels());

  chilitags.update(rgb);
}

//--------------------------------------------------------------
void ofApp::draw(){

  float w = ofGetWidth();
  float h = ofGetHeight();

  texRGB.draw(0, 0, w, h);
  texDepth.draw(w + 10, 0);

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
