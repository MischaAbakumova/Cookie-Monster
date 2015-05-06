//
//  killerVegie.h
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//

#ifndef __monster_cookie__killerVegie__
#define __monster_cookie__killerVegie__

#include <stdio.h>
#include <ofMain.h>

class killerVeggie{
public:
    
    killerVeggie();
    
    void setup(ofImage myVeggie);
    void update();
    void draw();
    
    ofImage enemyVeggie;
    ofVec2f enemyPosition;
    ofVec2f enemyVelocity;
    
     bool bKillEating;
    
    
    
};


#endif /* defined(__monster_cookie__killerVegie__) */
