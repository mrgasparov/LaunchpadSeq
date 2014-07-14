//
//  Pad.cpp
//  exampleInput
//
//  Created by Pedro Mendes on 11/06/14.
//
//

#include "Pad.h"

Pad::Pad(ofPoint _pos) {
    pos = _pos;
}

bool Pad::isActive() {
    return active;
}

ofPoint Pad::getPosition() {
    return pos;
}

void Pad::setPosition(ofPoint _pos) {
    pos = _pos;
}

