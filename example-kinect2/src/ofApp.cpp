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

  float s = 0.25;

  float w = rgb.getWidth()*s;
  float h = rgb.getHeight()*s;

  texRGB.draw(0, 0, w, h);
  texDepth.draw(w + 10, 0);

  vector<Tag>& tags = chilitags.tags();
  if (tags.empty())
    return;

  ofVec2f scale(w,h);

  ofPushStyle();
  ofSetColor(ofColor::red);
  for (int i = 0; i < tags.size(); i++)
  {
    vector<ofVec2f> &corners = tags[i].corners_n;
    ofVec2f p0,p1;
    for (int j = 0; j < corners.size(); j++)
    {
      p0 = corners[j] * scale;
      p1 = corners[ (j+1)%4 ] * scale;
      ofDrawLine( p0.x, p0.y, p1.x, p1.y );
    }
  }
  ofPopStyle();
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
