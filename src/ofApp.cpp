#include "ofApp.h"

float mouthThresh = 150;
float mouthClosedThresh = 100;

//--------------------------------------------------------------
void ofApp::setup(){
    
    gameStage = 0;
    
//    loading in all the necessary assets
    ofBackground(185,242,242);
    ofSetVerticalSync(true); //supposedly to prevent image tearing..doesn't seem to be doing anything
    ofSetFrameRate(60);  //runs at 60 fps for flicker-free experience
    ofEnableAlphaBlending();
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    camera.initGrabber(320, 240); //initiates the camera
    tracker.setup();  //ofxFaceTrackerThreaded tracker;
    
//    loading FONTS
    myFont.load("sourcesanspro-regular-webfont.ttf", 20, true,true);
    myFont.setLineHeight(20.0f);
    
//    loading IMAGES
    myImg.load("apple.png");
    killerImages.push_back(myImg);
    myImg.load("corn.png");
    killerImages.push_back(myImg);
    goodVeg.load("carrot.png");
    goodImages.push_back(goodVeg);
    goodVeg.load("pee.png");
    goodImages.push_back(goodVeg);
    goodVeg.load("broccoli.png");
    goodImages.push_back(goodVeg);
};

void ofApp::drawFood(){
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


void ofApp::start(){
    ofBackground(185,242,242); //set the color of  the background
    monsterPos.set(ofGetWindowWidth()/2, ofGetWindowHeight()/2); //the cookie monster is in the middle
    radius = 30;  //the initial size of the monster
    score = 0; //you havent eaten anything yet
    fat = 120;
    energyLevel = 100;
    drawFood();
};

void ofApp::update(){
    

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
//        float onCookie = ofDist(cookieList[0].position.x, cookieList[0].position.y, eyePos.x, eyePos.y);
//        ofPoint focus = cookieList[0].position;
//        //  leftEye.mousePos = focus;
//        //  rightEye.mousePos = focus;

    
};

void ofApp::draw(){
    cout<<"stage"<<gameStage<<endl;
    if(gameStage == INTRO_GAME_STATE) {
        intro();
    } else if (gameStage == GAME_STATE){
        game();
    } else if (gameStage == DEATH_SCREEN_STATE) {
        deathScreen();
    }
};

void ofApp::game() {
    ofBackground(185,242,242);
    ofSetColor(0,0,0);
    
// FACE POSITION
    faceTrackerUpdate();
    facePosition = tracker.getPosition();
    mappedPosition.x = ofMap(facePosition.x, 0, 320, 0, ofGetWindowWidth());
    mappedPosition.y = ofMap(facePosition.y, 0, 240, 0, ofGetWindowHeight());
    mappedPosition.x = ofGetWindowWidth()-mappedPosition.x; //mirrows the position on the x-axis
    monsterPos.x = mappedPosition.x;
    monsterPos.y = mappedPosition.y;
    cookieMonster(monsterPos.x, monsterPos.y);
    
//    MOUTH
    mouthWidth = tracker.getGesture(ofxFaceTracker::MOUTH_WIDTH)* 15;
    mouthHeight = tracker.getGesture(ofxFaceTracker::MOUTH_HEIGHT)* 20;
    
//    MONSTER EYES
    eyePos.set(monsterPos.x, monsterPos.y-75);
    leftEye.pos = ofPoint( eyePos.x - 35, eyePos.y );
    rightEye.pos = ofPoint( eyePos.x + 35, eyePos.y );
    leftEye.draw(mouseX, mouseY);
    rightEye.draw(mouseX, mouseY);
    
    ofPushMatrix();{
        ofSetColor(0);
        ofDrawEllipse(monsterPos.x, monsterPos.y+30, mouthWidth*0.7, mouthHeight*0.7);
        ofSetColor(255, 255, 255);
    }ofPopMatrix();
    
    
//    GUI
    myFont.drawString("COOKIE MONSTER: " + ofToString(score),50, 50); //still considering
    myFont.drawString("Energy" + ofToString(energyLevel), 50, 100);
    
    energyLevel = 100-ofGetElapsedTimef()*5;
    
    
    //comment this out if you don't need the tracker data
    //faceTrackerDraw();
    
//drawing COOKIES
    for (int i = 0; i<cookieList.size(); i++) {
        float distance = ofDist(monsterPos.x, monsterPos.y, cookieList[i].position.x, cookieList[i].position.y);
        if ( !cookieList[i].bEating ){
            if (distance < radius && mouthHeight > mouthThresh){
                cookieList[i].bEating = true;
            }
        } else {
            if ( distance < radius && mouthHeight < mouthClosedThresh ){
                cookieList.erase(cookieList.begin()+i);
                score += 2;
                fat += 15;
                energyLevel += 10;
            } else if (distance > radius * 2.) {
                cookieList[i].bEating = false;
            }
        }
        cookieList[i].draw();
    }
    
//drawing CHIKEN WINGS
    for (int i = 0; i<chickenWingList.size(); i++) {
        float distanceWings = ofDist(monsterPos.x, monsterPos.y, chickenWingList[i].wingPosition.x, chickenWingList[i].wingPosition.y);
        if(!chickenWingList[i].bChickenEating){
            if (distanceWings < radius && mouthHeight > mouthThresh){
                chickenWingList[i].bChickenEating = true;
            }
        } else {
            if(distanceWings < radius && mouthHeight < mouthClosedThresh){
                chickenWingList.erase(chickenWingList.begin()+i);
                score += 15;
                fat += 10;
                energyLevel += 15;
            }else if (distanceWings > radius*2.){
                chickenWingList[i].bChickenEating = false;
            }
        }
        chickenWingList[i].draw();
    }
    
//drawing GOOD VEGGIE
    for (int i = 0; i<healthyVeggieList.size(); i++) {
        float distanceGoodVeggie = ofDist(monsterPos.x, monsterPos.y, healthyVeggieList[i].veggiePosition.x, healthyVeggieList[i].veggiePosition.y);
        if(!healthyVeggieList[i].bVeggieEating){
            if(distanceGoodVeggie < radius && mouthHeight > mouthThresh) {
                healthyVeggieList[i].bVeggieEating = true;
            }
        }else{
            if (distanceGoodVeggie < radius && mouthHeight < mouthClosedThresh){
                healthyVeggieList.erase(healthyVeggieList.begin()+i);
                score += 5;
                fat -= 3;
                energyLevel +=1;
            } else if (distanceGoodVeggie > radius * 2.) {
                healthyVeggieList[i].bVeggieEating = false;
            }
        }
        healthyVeggieList[i].draw();
    }
    
//drawing KILLER VEGGIE
    for (int i = 0; i<killerVeggieList.size(); i++) {
        float distanceKillerVeggie = ofDist(monsterPos.x, monsterPos.y, killerVeggieList[i].enemyPosition.x, killerVeggieList[i].enemyPosition.y);
        if (!killerVeggieList[i].bKillEating){
            if(distanceKillerVeggie < radius && mouthHeight > mouthThresh) {
                killerVeggieList[i].bKillEating = true;
                //myFont.drawString("OH NO! GMO HAS FINALY GOT TO YOU", ofGetWidth()/2, ofGetHeight()/2);
            }
        }else{
            if (distanceKillerVeggie < radius && mouthHeight < mouthClosedThresh){
                killerVeggieList.erase(killerVeggieList.begin()+i);
            }else if (distanceKillerVeggie > radius * 2.){
                killerVeggieList[i].bKillEating = false;
            }
        }
        killerVeggieList[i].draw();
    }
    cout<<"fat :"<<fat<<endl;
    cout<<"energy :"<<energyLevel<<endl;
    
    if(energyLevel <= 0){
        gameStage = 2;
    }
};

void ofApp::deathScreen(){
    clearAll();
    myFont.drawString("CONGRADULATIONS!", ofGetWindowWidth()/2-100, ofGetWindowHeight()/2);
    myFont.drawString("YOUR SCORE IS "+ ofToString(score), ofGetWindowWidth()/2-100, ofGetWindowHeight()/2+50);
    myFont.drawString("Press 'RETURN' to try again", ofGetWindowWidth()/2-100, ofGetWindowHeight()/2+100);
}

//------------------------------------------FACE TRACK----------------------------------------------------------
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

void ofApp::faceTrackerDraw(){
    ofSetColor(255);
        camera.draw(0, 0, 640, 640);
    if(tracker.getFound()){
        ofSetLineWidth(1);
        tracker.draw();
    }
};

void ofApp::cookieMonster(float x, float y){
    ofPushMatrix();{
        ofTranslate(x, y);
        ofFill();
        ofSetColor(70, 118, 184);
        ofSetCircleResolution(100); //enables to draw fine circles
        ofDrawCircle(0, 0, fat); // will he get fat?
        ofSetColor(255, 255, 255);
    } ofPopMatrix();
};

//----------------GAME OVER--------------------------------
void ofApp::clearAll(){
        healthyVeggieList.clear();
        killerVeggieList.clear();
        cookieList.clear();
        chickenWingList.clear();
        ofBackground(0,0,0);

};

//-----------------------------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << "key: " << key << endl;
    
    if (key == 13 && gameStage != GAME_STATE){
        gameStage = 1;
        ofResetElapsedTimeCounter();
        cout << "after ihtg " << gameStage << endl;
        start();
    }
};

void ofApp::intro(){
    //an animation will be added to the intro to explain the impact of different types of food.
    ofBackground(255, 255, 255); //the background color is different from the one in the game
//    ofPushStyle();
        ofSetColor(0);
        myFont.drawString("PRESS 'RETURN' WHEN YOU ARE READY TO FEAST", 100, 100);
//    ofPopStyle();
}
