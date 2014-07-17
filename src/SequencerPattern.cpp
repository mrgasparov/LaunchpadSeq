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
    
    patternState = PATTERN_EMPTY;
    prevPatternState = PATTERN_EMPTY;
}

//--------------------------
// SequencerPattern Grid Methods
//--------------------------

SequencerPad* SequencerPattern::getPadAtPos(ofPoint _trPos) {
    
    SequencerPad *pad = &(sequencerPadMatrix[_trPos.x][_trPos.y]);

    return pad;
}


void SequencerPattern::toggleVelocity() {
    switch (patternState) {
            
        case PATTERN_EMPTY: {
            patternState = PATTERN_PLAY;
            active = true;
            break;
        }
        case PATTERN_PLAY: {
            patternState = PATTERN_STOP;
            active = false;
            break;
        }
        case PATTERN_STOP: {
            patternState = PATTERN_PLAY;
            active = true;
            break;
        }
        default: break;
    }
}




pattern_states_t SequencerPattern::getPatternState() {
    return patternState;
}

void SequencerPattern::setPatternState(pattern_states_t _patternState) {
    patternState = _patternState;
    
    if (patternState == PATTERN_EMPTY) {
        active = false;
    }
    else active = true;
}
