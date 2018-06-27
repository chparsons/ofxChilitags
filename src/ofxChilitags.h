#pragma once

#include "ofMain.h"
#include "ofThread.h"
#include "ofxCv.h"
#include "Poco/Condition.h"
#include <chilitags.hpp>

//TODO 
//3D

struct ChiliTag
{
  int id;

  vector<ofVec2f> corners;
  ofVec2f center;

  vector<ofVec2f> corners_n;
  ofVec2f center_n;

  ofVec2f dir;
  float angle;

  //ofVec3f translation;
  //struct Extrinsics { cv::Mat R, T; };
};

class ofxChilitags : public ofThread
{
  public:
    ofxChilitags();
    ~ofxChilitags(); 

    void init(bool threaded = true, int detection_period = 10, float fps_ = 30.0);
    void update(ofPixels &pixels);
    void render(float x = 0, float y = 0, float w = 640, float h = 480, ofColor color = ofColor::red);

    vector<ChiliTag>& tags();

    void fps(float v);
    float fps();
    float framerate();

  private:

    chilitags::Chilitags chilitags; 

    /*
     * trig = chilitags::Chilitags::ASYNC_DETECT_PERIODICALLY 
     * Runs the detection in the background, with a period, only tracking in the call to `find()`, period defaults to 15, i.e. out of 15 consecutive calls to `find()`, the background thread will be informed to run detection. After this, a new detection will be done as soon as a new image frame is presented in the call to `find()`. If the background thread takes more time than 15 calls to `find()`, it will be running as frequently as possible
     *
     * trig = chilitags::Chilitags::DETECT_PERIODICALLY
     * tracking most of the time, eventually run a full detection
     *
     * trig = chilitags::Chilitags::ASYNC_DETECT_ALWAYS
     * detection is run as frequently as possible, i.e a new detection is started as soon as the new image frame is presented in the call to `find()` after the previous detection is finished
     */
    chilitags::Chilitags::DetectionTrigger trig;

    ChiliTag make_tag(int id, const cv::Mat_<cv::Point2f> &corners, int width, int height);
    ofVec2f UP;

    /*
     * threaded logic based on ofxAruco
     * https://github.com/arturoc/ofxAruco
     */
    void findMarkers(ofPixels &pixels);
    vector<ChiliTag> markers, backMarkers, intraMarkers;
    ofPixels frontPixels, backPixels, intraPixels;
    bool newDetectMarkers, foundMarkers;
    Poco::Condition condition;
    void threadedFunction();
    bool threaded;

    //time in micros
    unsigned long long prev, lag, prev_proc, dt_micros;
    float _fps, micros_per_update, _dt_micros; 
};

