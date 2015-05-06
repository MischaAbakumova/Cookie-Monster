//
//  chicken.cpp
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//

#include "chicken.h"

chickenWing::chickenWing(){
    wing.loadImage("chicken-wing.png");
    wingVelocity.set(ofRandom(-0.2, 0.5),ofRandom(-0.2, 0.5));
    
}

void chickenWing::update(){
    wingPosition += wingVelocity;
    
    if (wingPosition.x < 0 || wingPosition.x >= ofGetWidth()-60) {
        //wingPosition.x = ofGetWidth();
        wingVelocity.x *= -1;
    }
    if (wingPosition.y < 0 ||wingPosition.y >= ofGetHeight()-60) {
        //wingPosition.y = ofGetHeight();
        wingVelocity.y *= -1;
    }
}

void chickenWing::draw(){
  
    
    ofPushStyle();
    if (bChickenEating) ofSetColor(255, 0, 0);
    wing.draw(wingPosition.x, wingPosition.y, 80, 80);
    ofPopStyle();
}