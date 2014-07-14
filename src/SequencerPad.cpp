//
//  Step.cpp
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#include "SequencerPad.h"

SequencerPad::SequencerPad() {
    cout << "created sp" << endl;
}

SequencerPad::SequencerPad(ofPoint _pos) {
    cout << "created sp" << endl;
    pos = _pos;
}

bool SequencerPad::isActive() {
    return active;
}

ofPoint SequencerPad::getPosition() {
    return pos;
}

void SequencerPad::setPosition(ofPoint _pos) {
    pos = _pos;
}

void SequencerPad::toggle() {
    
    switch (velocityState) {
        
        case VEL_OFF: {
            velocityState = VEL_MAX;
            active = true;
            break;
        }
        case VEL_MAX: {
            velocityState = VEL_OFF;
            active = false;
            break;
        }
        case VEL_MED: {
            velocityState = VEL_OFF;
            active = false;
            break;
        }
        case VEL_MIN: {
            velocityState = VEL_OFF;
            active = false;
            break;
        }
        default: break;
    }
}

void SequencerPad::toggleVelocity() {
    switch (velocityState) {
            
        case VEL_OFF: {
            velocityState = VEL_MAX;
            active = true;
            break;
        }
        case VEL_MAX: {
            velocityState = VEL_MED;
            active = true;
            break;
        }
        case VEL_MED: {
            velocityState = VEL_MIN;
            active = true;
            break;
        }
        case VEL_MIN: {
            velocityState = VEL_OFF;
            active = false;
            break;
        }
            
        default: break;
    }
}




velocity_states_t SequencerPad::getVelocityState() {
    return velocityState;
}

void SequencerPad::setVelocityState(velocity_states_t _velocityState) {
    velocityState = _velocityState;
    
    if (velocityState == VEL_OFF) {
        active = false;
    }
    else active = true;
}

void SequencerPad::toggleMute() {
    
    if(isActive()) {
        
        if(velocityState != VEL_MUTE) {
            prevVelocityState = velocityState;
            velocityState = VEL_MUTE;
            
            active = false;
        }
    }
    else {
        if(velocityState == VEL_MUTE) {
            velocityState = prevVelocityState;
            
            active = true;
        }
    }    
}