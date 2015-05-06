//
//  healthyVeggie.h
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//

#ifndef __monster_cookie__healthyVeggie__
#define __monster_cookie__healthyVeggie__

#include <stdio.h>
#include <ofMain.h>

class healthyVeggie{
public:
    
    void setup(ofImage hVeggie);
    void update();
    void draw();
    
    healthyVeggie();
    
    ofImage goodVeggie;
    ofVec2f veggiePosition;
    ofVec2f veggieVelocity;
    
    bool bVeggieEating;
    
};


#endif /* defined(__monster_cookie__healthyVeggie__) */
