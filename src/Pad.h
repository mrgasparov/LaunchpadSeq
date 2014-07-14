//
//  Pad.h
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#ifndef __exampleInput__Pad__
#define __exampleInput__Pad__

#include <iostream>

#include "ofMain.h"

#include "velocity_states_t.h"
#include "pad_colors_t.h"

class Pad {
    
public:
    
    Pad() {}
    Pad(ofPoint _pos);
    
    bool isActive();
    
    ofPoint getPosition();
    void setPosition(ofPoint pos);
    

    
    
    // is on?
    bool active = false;
    
    // position in grid
    ofPoint pos = ofPoint(0,0);
    
};


#endif /* defined(__exampleInput__Pad__) */
