//
//  chicken.h
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//

#ifndef __monster_cookie__chicken__
#define __monster_cookie__chicken__

#include <stdio.h>
#include "ofMain.h"


class chickenWing{
public:
    
    void update();
    void draw();
    

    chickenWing();
    
    
    ofImage wing;
    ofVec2f wingPosition;
    ofVec2f wingVelocity;
    
    
//------eating?-----------------
    bool bChickenEating;
    
};


#endif /* defined(__monster_cookie__chicken__) */
