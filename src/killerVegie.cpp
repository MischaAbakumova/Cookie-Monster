//
//  killerVegie.cpp
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//

#include "killerVegie.h"

killerVeggie::killerVeggie(){
    
    //enemyVeggie.loadImage("apple.png");
    enemyVelocity.set(ofRandom(-0.5, .5), ofRandom(-0.5, .5));
    
}

void killerVeggie::setup(ofImage myVeggie){
    enemyVeggie = myVeggie;
}

void killerVeggie::update(){
    enemyPosition += enemyVelocity;
    
    if(enemyPosition.x < 0 || enemyPosition.x >= ofGetWidth()-80){
        enemyVelocity.x *= -1;
    }
    if(enemyPosition.y < 0 || enemyPosition.y >= ofGetHeight()-80){
        enemyVelocity.y *= -1;
    }
}

void killerVeggie::draw(){
    
    ofPushStyle();
    if (bKillEating) ofSetColor(255, 0, 0);
     enemyVeggie.draw(enemyPosition.x-40, enemyPosition.y-40, 80, 80);
    ofPopStyle();
   
}