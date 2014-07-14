//
//  SequencerPattern.h
//  LaunchpadSeq
//
//  Created by Pedro Mendes on 14/07/14.
//
//

#ifndef __LaunchpadSeq__SequencerPattern__
#define __LaunchpadSeq__SequencerPattern__

#include <iostream>

#include "ofMain.h"

#include "SequencerPad.h"

#include "op_direction_t.h"
#include "pattern_states_t.h"

class SequencerPattern
{
public:
    
    SequencerPattern() :
    sequencerPadMatrix(32, std::vector<SequencerPad>(32, SequencerPad()))
    {};
    
    void init();
    
    //--------------------------
    // Sequencer Grid Methods
    //--------------------------

    SequencerPad* getPadAtPos(ofPoint _pos);
 
    void toggleVelocity();
    
    pattern_states_t getVelocityState();
    void setVelocityState(pattern_states_t _velocityState);
    
    bool isActive();
    
private:
    
    //--------------------------
    // Sequencer Grid Attributes
    //--------------------------
    
    // 32 track x 32 step grid used to store whole SequencerPattern
    std::vector<std::vector<SequencerPad> > sequencerPadMatrix;
    
    
    // velocity state, starts OFF
    pattern_states_t velocityState = PATTERN_EMPTY;
    pattern_states_t prevVelocityState = PATTERN_EMPTY;
    
    // is on?
    bool active = false;
};



#endif /* defined(__LaunchpadSeq__SequencerPattern__) */
