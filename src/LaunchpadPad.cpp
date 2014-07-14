//
//  LaunchpadPad.cpp
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#include "LaunchpadPad.h"

LaunchpadPad::LaunchpadPad(ofPoint _pos) {
    pos = _pos;
}



ofPoint LaunchpadPad::getPosition() {
    return pos;
}

void LaunchpadPad::setPosition(ofPoint _pos) {
    pos = _pos;
}



void LaunchpadPad::setAddressXYMode(int _address) {
    addressXYMode = _address;
}

int LaunchpadPad::getAddressXYMode() {
    return addressXYMode;
}

void LaunchpadPad::setAddressDrumMode(int _address) {
    addressDrumMode = _address;
}

int LaunchpadPad::getAddressDrumMode() {
    return addressDrumMode;
}



pad_colors_t LaunchpadPad::getPadColor() {
    return padColor;
}

void LaunchpadPad::setPadColor(pad_colors_t _padColor) {
    prevPadColor = padColor;
    padColor = _padColor;
}

void LaunchpadPad::togglePadColor() {
    prevPadColor = padColor;
    
    switch(padColor) {
        case OFF: {
            setPadColor(ORANGE_FULL);
            break;
        }
        case ORANGE_FULL: {
            setPadColor(OFF);
            break;
        }
        default: break;
    }
}

bool LaunchpadPad::colorChanged() {
    if(padColor != prevPadColor) return true;
    else return false;
}



void LaunchpadPad::printColor() {
    prevPadColor = padColor;
}