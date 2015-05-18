#include "ofApp.h"

float mouthThresh = 150;
float mouthClosedThresh = 100;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    
    camera.initGrabber(320, 240); //init the camera
    tracker.setup();
    start();
  
    
    myFont.loadFont("myFont.ttf", 20);
    
};

void ofApp::start(){

    ofBackground(255, 255, 255);
    radius = 30;
    score = 0;
    playTimer = 0;
    fat = 120;
    gameStage = 0;
   
    
    username = "Enter Your Name";
    enterName = false;

    
    
    //----------LOADIING IMAGES--------------------------------------
    ofImage myImg;
    ofImage goodVeg;
    myImg.loadImage("apple.png");
    killerImages.push_back(myImg);
    myImg.loadImage("corn.png");
    killerImages.push_back(myImg);
    goodVeg.loadImage("carrot.png");
    goodImages.push_back(goodVeg);
    goodVeg.loadImage("pee.png");
    goodImages.push_back(goodVeg);
    goodVeg.loadImage("broccoli.png");
    goodImages.push_back(goodVeg);
    //------------------------------------------------------------------
    
    
   
    
    for (int i = 0; i < 15; i++){
        cookie p;
        p.position.set(ofRandomWidth(), ofRandomHeight());
        cookieList.push_back(p); //adds a new element to the end of the array.
    }
    for (int i = 0; i < 20; i++){
        chickenWing wng;
        wng.wingPosition.set(ofRandomWidth(), ofRandomHeight());
        chickenWingList.push_back(wng); //adds a new element to the end of the array.
    }
    
    for (int i = 0; i < 15; i++){
        healthyVeggie veg;
        int randomImage = round(ofRandom(goodImages.size()-1));
        ofImage myGoodImg = goodImages [randomImage];
        veg.setup(myGoodImg);
        veg.veggiePosition.set(ofRandomWidth(), ofRandomHeight());
        healthyVeggieList.push_back(veg);
    }
    
    
    for(int i =0; i < 15; i++){
        killerVeggie kill;
        
        int randomNum = round(ofRandom(killerImages.size() - 1));
        ofImage myRandomImg = killerImages[randomNum];
        kill.setup(myRandomImg);
        kill.enemyPosition.set(ofRandomWidth(), ofRandomHeight());
        killerVeggieList.push_back(kill);
    }
    

};

//----------------UPDATE-----------------------------------------------
void ofApp::update(){
    
    faceTrackerUpdate();
    
  
//---------------MOUTH OPENING-----------------------------------------

    mouthWidth = tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH)* 15;
    mouthHeight = tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT)* 20;
    
//--------------CHARACTER MOVING---------------------------------------
    
    ofVec2f mappedPosition;
    ofVec2f facePosition;
    
    
    facePosition = tracker.getPosition();
//    cout<<facePosition<<"\n";
    mappedPosition.x = ofMap(facePosition.x, 0, 320, 0, ofGetWindowWidth());
    mappedPosition.y = ofMap(facePosition.y, 0, 240, 0, ofGetWindowHeight());
    mappedPosition.x = ofGetWindowWidth()-mappedPosition.x; //mirrows the position on the x-axis
  
    
    monsterPos.x = mappedPosition.x;
    monsterPos.y = mappedPosition.y;
    
    eyePos.set(monsterPos.x, monsterPos.y-75);
    leftEye.pos = ofPoint( eyePos.x - 35, eyePos.y );
    rightEye.pos = ofPoint( eyePos.x + 35, eyePos.y );
    

    
    
  //---------UPDATING POSITIONS OF ELEMENTS---------------------
    for (int i = 0; i<cookieList.size(); i++) {
        cookieList[i].update();
    }
    for (int i = 0; i<chickenWingList.size(); i++) {
        chickenWingList[i].update();
    }
    
    for (int i = 0; i<healthyVeggieList.size(); i++) {
        healthyVeggieList[i].update();
    }
    
    for (int i = 0; i < killerVeggieList.size(); i++) {
        killerVeggieList[i].update();
    }
    
    
    //-----------Focusing on a Cookie----------------------------------------
    float onCookie = ofDist(cookieList[0].position.x, cookieList[0].position.y, eyePos.x, eyePos.y);
    ofPoint focus = cookieList[0].position;
    //  leftEye.mousePos = focus;
    //    rightEye.mousePos = focus;


};

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(gameStage == 0){
        ofBackground(255, 255, 255);
        ofPushStyle();{
        ofSetColor(0);
        myFont.drawString("YOU HAVE ONE MINUTE TO EAT AS MUCH AS YOU CAN!", ofGetWindowWidth()/2, 300);
        myFont.drawString("PRESS 'RETURN' WHEN YOU ARE READY", ofGetWindowWidth()/2, ofGetWindowHeight()/2 + 300);
        }ofPopStyle();
    }
    
    else if (gameStage ==1);{
    
    
    ofBackground(255,255,255);
    
    ofSetColor(0,0,0);
    playTimer = (60-ofGetElapsedTimef());
    //------------------------------DISPLAY NUMBERS------------------------------
    myFont.drawString("COOKIE MONSTER: " + ofToString(score),50, 50); //experiment
    myFont.drawString("TIME: "+ ofToString(playTimer), 1270, 50);
    
  //------------------------MY MONSTER------------------------------
    cookieMonster(monsterPos.x, monsterPos.y);
    leftEye.draw(mouseX, mouseY);
    rightEye.draw(mouseX, mouseY);
   
    
    //comment this out if you don't need the tracker data
    //faceTrackerDraw();
    
    //----------DRAW MOUTH------------------------------------
   
    ofPushMatrix();{
    ofSetColor(0);
    ofEllipse(monsterPos.x, monsterPos.y+30, mouthWidth*0.7, mouthHeight*0.7);
    ofSetColor(255, 255, 255);
    }ofPopMatrix();
        
   

    //drawing COOKIES
    for (int i = 0; i<cookieList.size(); i++) {
       //--------------------------eat a cookie--------------------------------------------------
        float distance = ofDist(monsterPos.x, monsterPos.y, cookieList[i].position.x, cookieList[i].position.y);
        
        // currently not being eaten
        if ( !cookieList[i].bEating ){
            // mouth is big enough to eat!
            if (distance < radius && mouthHeight > mouthThresh){
                cookieList[i].bEating = true;
            }
        // being eaten
        } else {
            if ( distance < radius && mouthHeight < mouthClosedThresh ){
                cookieList.erase(cookieList.begin()+i);
                score += 10;
                fat += 2.8;
            } else if (distance > radius * 2.) {
                cookieList[i].bEating = false;
            }
        }
        cookieList[i].draw();
       
//        ofDrawBitmapString(ofToString(distance), cookieList[i].position);
    }
        
            //drawing CHIKEN WINGS
    
    for (int i = 0; i<chickenWingList.size(); i++) {
        //---------------------------eat a chicken---------------------------------------------
        float distanceWings = ofDist(monsterPos.x, monsterPos.y, chickenWingList[i].wingPosition.x, chickenWingList[i].wingPosition.y);
        
        //currently not being eaten
        if( !chickenWingList[i].bChickenEating){
            //mouth is big enough
        if (distanceWings < radius && mouthHeight > mouthThresh){
            chickenWingList[i].bChickenEating = true;
        }
            //being eaten
        } else {
            if(distanceWings < radius && mouthHeight < mouthClosedThresh){
              chickenWingList.erase(chickenWingList.begin()+i);
                score += 15;
                fat += 4.5;
            }else if (distanceWings > radius*2.){
                chickenWingList[i].bChickenEating = false;
            }
        }
        
        chickenWingList[i].draw();
       // ofDrawBitmapString(ofToString(distanceWings), chickenWingList[i].wingPosition);
        
    }
    
    
    //drawing GOOD VEGGIE
    
    for (int i = 0; i<healthyVeggieList.size(); i++) {
        
  //------------------eating good veggie-----------------------------------------
        float distanceGoodVeggie = ofDist(monsterPos.x, monsterPos.y, healthyVeggieList[i].veggiePosition.x, healthyVeggieList[i].veggiePosition.y);
        
        //not being eaten
        if(!healthyVeggieList[i].bVeggieEating){
            
        //mouth is big enough
            if(distanceGoodVeggie < radius && mouthHeight > mouthThresh) {
                healthyVeggieList[i].bVeggieEating = true;
            }
            //being eaten
        }else{
        if (distanceGoodVeggie < radius && mouthHeight < mouthClosedThresh){
            healthyVeggieList.erase(healthyVeggieList.begin()+i);
            score += 5;
            fat -= 3;
        } else if (distanceGoodVeggie > radius * 2.) {
            healthyVeggieList[i].bVeggieEating = false;
        }
        }
        healthyVeggieList[i].draw();
    }
    
    //drawing KILLER VEGGIE
    
    for (int i = 0; i<killerVeggieList.size(); i++) {
        
        //----------------eating a killer veggie ---------------------------------------------------------------
        float distanceKillerVeggie = ofDist(monsterPos.x, monsterPos.y, killerVeggieList[i].enemyPosition.x, killerVeggieList[i].enemyPosition.y);
        
        //not being eaten
        if (!killerVeggieList[i].bKillEating){
         //mouth is big enough
            if(distanceKillerVeggie < radius && mouthHeight > mouthThresh) {
                killerVeggieList[i].bKillEating = true;
            }
         //being eaten
        }else{
        if (distanceKillerVeggie < radius && mouthHeight < mouthClosedThresh){
            killerVeggieList.erase(killerVeggieList.begin()+i);
            
            
        }else if (distanceKillerVeggie > radius * 2.){
            killerVeggieList[i].bKillEating = false;
            
        }

    }
        killerVeggieList[i].draw();
    }
    
    if(playTimer <= 0){
        clearAll();
    }
    }
    
        
        //----------------------Done with Veggies----------------------------------------------------

};


void ofApp::faceTrackerUpdate(){
    camera.update();
    if(camera.isFrameNew()) {
        tracker.update(toCv(camera));
        position = tracker.getPosition();
        scale = tracker.getScale();
        orientation = tracker.getOrientation();
        rotationMatrix = tracker.getRotationMatrix();
    }
    
};

//-------------FACE TRACK-----------------------------------------------------
void ofApp::faceTrackerDraw(){
    ofSetColor(255);
        camera.draw(0, 0, 640, 480);
    if(tracker.getFound()){
        ofSetLineWidth(1);
//        ofFill();
        tracker.draw();
    
    }
};
//-------------Monster Creation---------------------------------------------
void ofApp::cookieMonster(float x, float y){
    ofPushMatrix();{
        ofTranslate(x, y);
        ofFill();
        ofSetColor(70, 118, 184);
        ofSetCircleResolution(100); //enables to draw fine circles
        ofCircle(0, 0, fat); // will he get fat?
        ofSetColor(255, 255, 255);
    } ofPopMatrix();
};

//----------------congratulation, you won--------------------------------
void ofApp::clearAll(){
    if (playTimer <= 0){
        healthyVeggieList.clear();
        killerVeggieList.clear();
        cookieList.clear();
        chickenWingList.clear();
        ofPushStyle();{
        ofBackground(0,0,0);
        myFont.drawString("CONGRADULATIONS!", ofGetWindowWidth()/2-100, ofGetWindowHeight()/2);
        myFont.drawString("YOUR SCORE IS "+ ofToString(score), ofGetWindowWidth()/2-100, ofGetWindowHeight()/2+50);
        myFont.drawString("Press 'RETURN' to try again", ofGetWindowWidth()/2-100, ofGetWindowHeight()/2+100);
        }ofPopStyle();
    }

};
//-----------------------------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key << endl;
    
    if (key == OF_KEY_RETURN){
        gameStage ++;
        ofResetElapsedTimeCounter();
        start();
    }
    
//        if(enterName){
//            if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
//                username = username.substr(0, username.length()-1);
//    
//            }
//                username.append(1, (char)key);
//            }

};

