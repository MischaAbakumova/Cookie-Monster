//
//  cookie.cpp
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//


#include "cookie.h"
cookie::cookie(){
    cookies.load("cookies-cartoon.png");
    velocity.set(ofRandom(-2,1),ofRandom(-2,1));
    
    bEating = false;
}


void cookie::update(){
    position += velocity;
    
    //bouncing off the screen
    if (position.x < 0 || position.x >= ofGetWidth()-50) {
        velocity.x *= -1;
    }
    if (position.y < 0 || position.y >= ofGetHeight()-50) {
        velocity.y *= -1;
    }
    
}

void cookie::draw(){
  
    ofPushStyle();
    if (bEating) ofSetColor(255, 0, 0);
        cookies.draw(position.x, position.y, 50, 50);
    
    ofPopStyle();
}