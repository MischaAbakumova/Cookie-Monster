#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxCv.h"
#include "cookie.h"
#include "chicken.h"
#include "healthyVeggie.h"
#include "killerVegie.h"

using namespace ofxCv;
using namespace cv;

class Eyes {
public:
    
    ofVec3f pos;
    float angle;
    
    void draw(float mouseX, float mouseY) {
        ofPushMatrix();{
            ofTranslate( pos );
            ofScale(0.6f,0.6f);
            float x = mouseX - pos.x;
            float y = mouseY - pos.y;
            
            angle = atan2( y , x ) ;
            ofRotate( ofRadToDeg(angle) );
            
           //---------eyeballs----------------------
            ofSetColor( 255 );
            ofCircle(0, 0, 70);
            
            //--------irisis-------------------------
            ofSetColor( 0 );
            ofCircle(20, 0, 20);
        }ofPopMatrix();
    }
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void start();
        void cookieMonster(float x, float y);
        void faceTrackerUpdate();
        void faceTrackerDraw();
        void clearAll();
        void keyPressed(int key);
    
    void exit(){
        tracker.waitForThread();
    }
  
    //------CAMERA STEUP-------------------------------------------
    
    ofVideoGrabber camera;
    ofxFaceTrackerThreaded tracker;      // taken from
    ofVec2f position;           // Kyle Mcdonald Face TRack example
    float scale;                //  https://github.com/kylemcdonald/ofxFaceTracker
    ofVec3f orientation;        //
    ofMatrix4x4 rotationMatrix; //
    

    //------MONSTER MOVING---------------------------------------------------
    
    ofVec2f monsterPos;
    float mouthWidth;
    float mouthHeight;
    
    vector<cookie> cookieList; //creates an empty array of cookies
    vector<chickenWing> chickenWingList; // creates an array of wings
    vector<healthyVeggie>healthyVeggieList; //creates an array of veggies
    vector<killerVeggie>killerVeggieList; //creates an array of poison veggie
    vector<string> saveName;
    
    vector<ofImage> killerImages;
    vector<ofImage> goodImages;
    
    Eyes rightEye, leftEye;
    ofVec2f eyePos;
    
    float radius;
    float fat;
    int score;
    int playTimer;
    int gameStage;
    string username;
    bool enterName;
    ofTrueTypeFont myFont;
    
    
    
};
