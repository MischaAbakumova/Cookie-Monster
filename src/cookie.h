//
//  cookie.h
//  monster_cookie
//
//  Created by Mischa Abakumova on 4/22/15.
//
//
#pragma once
#ifndef __monster_cookie__cookie__
#define __monster_cookie__cookie__

#include <stdio.h>
#include "ofMain.h" //adds the entire OpenFrameworks library to the main.cpp class

class cookie{
    
public:
    
    //methods
    void update();
    void draw();
    
    //constructor
    cookie();
    
    //vatiables
    ofImage cookies;
    ofVec2f position;
    ofVec2f velocity;
    
    // eating?
    bool bEating;
};






#endif /* defined(__monster_cookie__cookie__) */
