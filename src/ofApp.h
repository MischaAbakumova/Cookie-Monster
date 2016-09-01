#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxCv.h"
#include "cookie.h"
#include "chicken.h"
#include "healthyVeggie.h"
#include "killerVegie.h"
#include "ofxGui.h"

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
            ofRotate(ofRadToDeg(angle));
            
           //---------eyeballs----------------------
            ofSetColor( 255 );
            ofDrawCircle(0, 0, 70);
            
            //--------irisis-------------------------
            ofSetColor( 0 );
            ofDrawCircle(20, 0, 20);
        }ofPopMatrix();
    }
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void start();
        void restart();
        void game();
        void cookieMonster(float x, float y);
        void faceTrackerUpdate();
        void faceTrackerDraw();
        void clearAll();
        void keyPressed(int key);
        void gameOver();
        void intro();
        void deathScreen();
        void drawFood();
    
        void exit(){
        tracker.waitForThread();
    }
  
    //----------------------------CAMERA STEUP----------------------------------------------------------------------------------------
    // taken from Kyle Mcdonald Face TRack example https://github.com/kylemcdonald/ofxFaceTracker
    
    ofVideoGrabber camera;
    ofxFaceTrackerThreaded tracker;
    ofVec2f position;
    float scale;
    ofVec3f orientation;
    ofMatrix4x4 rotationMatrix;
    

    //---------------------------MONSTER MOVING-------------------------------------------------------------------------------------
    ofVec2f mappedPosition;
    ofVec2f facePosition;
    ofVec2f monsterPos;
    float mouthWidth;
    float mouthHeight;
    
    //----------------------------LOADS THE IMAGES-----------------------------------------------------------------------------------
    vector<cookie> cookieList; //creates an empty array of cookies
    vector<chickenWing> chickenWingList; // creates an array of wings
    vector<healthyVeggie>healthyVeggieList; //creates an array of veggies
    vector<killerVeggie>killerVeggieList; //creates an array of veggies that will kill the monster
    vector<ofImage> killerImages;
    vector<ofImage> goodImages;
    ofImage myImg;
    ofImage goodVeg;

    
    Eyes rightEye, leftEye;
    ofVec2f eyePos;
    
    float radius;
    float fat;
    int score;
    
    //------------------------------------UI elements-----------------------------------------------------------
    int playTimer;
    int gameStage;
    ofTrueTypeFont myFont;
    int energyLevel;
    int energyTimer;
    
    
    int INTRO_GAME_STATE = 0;
    int GAME_STATE = 1;
    int DEATH_SCREEN_STATE = 2;
    
    
};
