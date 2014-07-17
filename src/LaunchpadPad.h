//
//  LaunchpadPad.h
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#ifndef __exampleInput__LaunchpadPad__
#define __exampleInput__LaunchpadPad__

#include "ofMain.h"

#include "pad_colors_t.h"

class LaunchpadPad {
    
public:
    
    LaunchpadPad() {}
    LaunchpadPad(ofPoint _pos);
    
    ofPoint getPosition();
    void setPosition(ofPoint pos);
    
    void setAddressXYMode(int _address);
    int getAddressXYMode();
    
    void setAddressDrumMode(int _address);
    int getAddressDrumMode();
    
    pad_colors_t getPadColor();
    void setPadColor(pad_colors_t _padColor);
    
    void togglePadColor();
    
    bool colorChanged();
    
    void printColor();
    
private:
    
    // position in matrix
    ofPoint pos;
    
    // color
    pad_colors_t padColor = RED_FULL;
    // prev pad color starts with diff value so that all pads are updated to OFF on first run
    pad_colors_t prevPadColor = OFF;
    
    
    int addressXYMode = -1;
    int addressDrumMode = -1;
};

#endif /* defined(__exampleInput__LaunchpadPad__) */
