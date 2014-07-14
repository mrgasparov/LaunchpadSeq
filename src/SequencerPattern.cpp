//
//  SequencerPattern.cpp
//  LaunchpadSeq
//
//  Created by Pedro Mendes on 14/07/14.
//
//

#include "SequencerPattern.h"

void SequencerPattern::init() {
    // create blank sequencer grid
    for(int y = 0; y < 32; y++) {
     for(int x = 0; x < 32; x++) {
     
     SequencerPad *pad = &(sequencerPadMatrix[x][y]);
     pad->setPosition(ofPoint(x, y));
     }
    }
}

//--------------------------
// SequencerPattern Grid Methods
//--------------------------

SequencerPad* SequencerPattern::getPadAtPos(ofPoint _trPos) {
    
    SequencerPad *pad = &(sequencerPadMatrix[_trPos.x][_trPos.y]);

    return pad;
}


void SequencerPattern::toggleVelocity() {
    switch (velocityState) {
            
        case PATTERN_EMPTY: {
            velocityState = PATTERN_PLAY;
            active = true;
            break;
        }
        case PATTERN_PLAY: {
            velocityState = PATTERN_STOP;
            active = false;
            break;
        }
        case PATTERN_STOP: {
            velocityState = PATTERN_PLAY;
            active = true;
            break;
        }
        default: break;
    }
}




pattern_states_t SequencerPattern::getVelocityState() {
    return velocityState;
}

void SequencerPattern::setVelocityState(pattern_states_t _velocityState) {
    velocityState = _velocityState;
    
    if (velocityState == PATTERN_EMPTY) {
        active = false;
    }
    else active = true;
}
