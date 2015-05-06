//
//  healthyVeggie.cpp
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//

#include "healthyVeggie.h"

healthyVeggie::healthyVeggie(){
    goodVeggie.loadImage("eggplant.png");
    veggieVelocity.set(ofRandom(-0.2, 0.5),ofRandom(-0.2, 0.5));
    
}

void healthyVeggie::setup(ofImage hVeggie){
    goodVeggie = hVeggie;
}

void healthyVeggie::update(){
    veggiePosition += veggieVelocity;
    
    if (veggiePosition.x < 0 || veggiePosition.x >= ofGetWidth()) {
        //wingPosition.x = ofGetWidth();
        veggieVelocity.x *= -1;
    }
    if (veggiePosition.y < 0 ||veggiePosition.y >= ofGetHeight()) {
        //wingPosition.y = ofGetHeight();
        veggieVelocity.y *= -1;
    }
}

void healthyVeggie::draw(){
    
    ofPushStyle();
    if (bVeggieEating) ofSetColor(255, 0, 0);
    goodVeggie.draw(veggiePosition.x, veggiePosition.y, 60, 60);
    
    ofPopStyle();
    
   
}

