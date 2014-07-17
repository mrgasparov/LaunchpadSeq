//
//  Step.h
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#ifndef __exampleInput__Step__
#define __exampleInput__Step__

#include <iostream>

#include "ofMain.h"

#include "velocity_states_t.h"

class SequencerPad {

public:
    
    SequencerPad();
    SequencerPad(ofPoint _pos);
    
    void toggle();
    void toggleVelocity();
    void toggleMute();
    
    bool isActive();
    
    ofPoint getPosition();
    void setPosition(ofPoint _pos);
    
    velocity_states_t getVelocityState();
    void setVelocityState(velocity_states_t _velocityState);
    
    
    
    
private:
    
    // velocity state, starts OFF
    velocity_states_t velocityState = VEL_OFF;
    velocity_states_t prevVelocityState = VEL_OFF;
    
    // is on?
    bool active = false;
    
    // position in grid
    ofPoint pos;
    
};


#endif /* defined(__exampleInput__Step__) */
