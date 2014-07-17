//
//  Sequencer.cpp
//  exampleInput
//
//  Created by Pedro Mendes on 10/06/14.
//
//

#include "Sequencer.h"

// Global static pointer used to ensure a single instance of the class.
Sequencer* Sequencer::m_pInstance = NULL;

/** This function is called to create an instance of the class.
 Calling the constructor publicly is not allowed. The constructor
 is private and is only called by this Instance function.
 */

Sequencer* Sequencer::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new Sequencer;
    
    return m_pInstance;
}


void Sequencer::init()
{
    // initialize pattern bank
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            
            SequencerPattern *pattern = &(patternBank[x][y]);
            pattern->init();
        }
    }
    
    // initialize first pattern
    patternBank[currentPattern.x][currentPattern.y].toggleVelocity();
    
    // init the timer
    initTimer(25);
}

void Sequencer::update() {
    
    // increment step sequence if timer active
    
    if (isRunning && checkTimer()) {
        
        Launchpad::Instance()->updateMatrix();
        Launchpad::Instance()->displayButtons();
        
        Launchpad::Instance()->displayMatrix();
    }
}

void Sequencer::toggleFollowMode() {
    followMode = !followMode;
}

bool Sequencer::isFollowMode() {
    return followMode;
}

void Sequencer::toggleVelocityMode() {
    velocityMode = !velocityMode;
}

bool Sequencer::isVelocityMode() {
    return velocityMode;
}


//--------------------------
// Sequencer Grid Methods
//--------------------------

void Sequencer::togglePadAtPos(ofPoint _pos) {
    
    ofPoint trPos = translatePadPosition(_pos);
    
    SequencerPad *pad = patternBank[currentPattern.x][currentPattern.y].getPadAtPos(trPos);
    
    if(isVelocityMode()) pad->toggleVelocity();
    else pad->toggle();
    ExternalMIDI::Instance()->sendNoteOn((pad->getPosition().y + 32),
                                         pad->getVelocityState());
}

pad_colors_t Sequencer::getPadColorAtPos(ofPoint _pos) {

    ofPoint trPos = translatePadPosition(_pos);
    SequencerPad *pad = patternBank[currentPattern.x][currentPattern.y].getPadAtPos(trPos);
    
    pad_colors_t pc = OFF;
    
    switch (pad->getVelocityState()) {
        case VEL_OFF: pc = OFF; break;
        case VEL_MIN: pc = GREEN_DIM; break;
        case VEL_MED: pc = GREEN_MED; break;
        case VEL_MAX: pc = GREEN_FULL; break;
        case VEL_MUTE: pc = RED_DIM; break;
        default: break;
    }
    
    return pc;
}



ofPoint Sequencer::translatePadPosition(ofPoint _pos) {
    ofPoint trPos = ofPoint(_pos.x + (editPage * (NUM_STEPS / NUM_PAGES)),
                            _pos.y + topTrack);
    return trPos;
}


// gets a list of SequencerPads that are active on a given step
std::vector<SequencerPad*> Sequencer::getActivePadsAtStep(int _step) {
    
    std::vector<SequencerPad*> padVector;
    
    for(int t = 0; t < NUM_TRACKS; t++) {
        
        SequencerPad *pad = patternBank[currentPattern.x][currentPattern.y].getPadAtPos(ofPoint(_step, t));
        
        if(pad->isActive()) {
            padVector.push_back(pad);
        }
    }
    return padVector;
}


void Sequencer::mutePadLine(int _y) {
    for(int x = 0; x < NUM_STEPS; x++) {
        ofPoint trPos = translatePadPosition(ofPoint(0,_y));
        // little trick so that translation doesn't displace x
        // maybe do separate method to translate just 1 axis
        trPos.x = x;
        
        SequencerPad *pad = patternBank[currentPattern.x][currentPattern.y].getPadAtPos(trPos);
        
        pad->toggleMute();
    }
}

void Sequencer::deletePadLine(int _y) {
    for(int x = 0; x < NUM_STEPS; x++) {
        ofPoint trPos = translatePadPosition(ofPoint(0,_y));
        trPos.x = x;
        
        SequencerPad *pad = patternBank[currentPattern.x][currentPattern.y].getPadAtPos(trPos);
        
        pad->setVelocityState(VEL_OFF);
    }
}


void Sequencer::copyPage(op_direction_t _dir) {
    
    int originStartStep = editPage * 8;
    int destinationStartStep = -1;

    // calculate the destination start step
    switch (_dir) {
        case LEFT: {

            if (editPage <= 0) {
                destinationStartStep = NUM_STEPS - 8;
                
                editPage = 3;
            }
            else {
                destinationStartStep = originStartStep - 8;
                
                editPage--;
            }

            break;
        }
        case RIGHT: {
            
            if (editPage >= 3) {
                destinationStartStep = 0;
                
                editPage = 0;
            }
            else {
                destinationStartStep = originStartStep + 8;
                
                editPage++;
            }
            
            break;
        }
        default: break;
    }

    
    if(destinationStartStep != -1) {
        
        for(int x = 0; x < 8; x++) {
            
            for(int y = 0; y < NUM_TRACKS; y++) {
                ofPoint originPos = ofPoint((originStartStep + x),y);
                ofPoint destinationPos = ofPoint((destinationStartStep + x),y);
                
                SequencerPad *originPad = patternBank[currentPattern.x][currentPattern.y].getPadAtPos(originPos);
                SequencerPad *destinationPad = patternBank[currentPattern.x][currentPattern.y].getPadAtPos(destinationPos);
                
                destinationPad->setVelocityState(originPad->getVelocityState());
            }
            
        }

    }
}



void Sequencer::togglePatternAtPos(ofPoint _pos) {
    prevPattern = currentPattern;
    currentPattern = _pos;
    
    patternBank[prevPattern.x][prevPattern.y].toggleVelocity();
    patternBank[currentPattern.x][currentPattern.y].toggleVelocity();
}

void Sequencer::resetPatternAtPos(ofPoint _pos) {
    
    patternBank[_pos.x][_pos.y].init();
}

void Sequencer::copyPatternToPos(ofPoint _pos) {
    
    // copy pattern bank
    patternBank[_pos.x][_pos.y] = patternBank[currentPattern.x][currentPattern.y];
    
    prevPattern = currentPattern;
    currentPattern = _pos;
    
    patternBank[prevPattern.x][prevPattern.y].toggleVelocity();
    //patternBank[currentPattern.x][currentPattern.y].toggleVelocity();
}


pad_colors_t Sequencer::getPatternColorAtPos(ofPoint _pos) {
    
    SequencerPattern *pattern = &(patternBank[_pos.x][_pos.y]);
    
    pad_colors_t pc = OFF;
    
    switch (pattern->getPatternState()) {
        case PATTERN_EMPTY: pc = OFF; break;
        case PATTERN_PLAY: pc = GREEN_FULL; break;
        case PATTERN_STOP: pc = GREEN_DIM; break;
        default: break;
    }
    
    return pc;
}

//----------------------------
// Sequencer Edit View Methods
//----------------------------

void Sequencer::setEditPage(int _page) {
    editPage = _page;
}

int Sequencer::getEditPage() {
    return editPage;
}

void Sequencer::incEditPage() {
    editPage++;
    if(editPage > MAX_EDIT_PAGE) editPage = MAX_EDIT_PAGE;
}
void Sequencer::decEditPage() {
    editPage--;
    if(editPage < MIN_EDIT_PAGE) editPage = MIN_EDIT_PAGE;
}

void Sequencer::setTopTrack(int _track) {
    topTrack = _track;
}
int Sequencer::getTopTrack() {
    return topTrack;
}

void Sequencer::incTopTrack() {
    topTrack++;
    if(topTrack > MAX_TOP_TRACK) topTrack = MAX_TOP_TRACK;
}
void Sequencer::decTopTrack() {
    topTrack--;
    if(topTrack < MIN_TOP_TRACK) topTrack = MIN_TOP_TRACK;
}


//--------------------------
// Sequencer Step Methods
//--------------------------

void Sequencer::setStepInc(float _stepInc) {
    stepInc = _stepInc;
}

void Sequencer::incStep() {
    if(isRunning) {
        currentStep += stepInc;
        currentStep = (int)currentStep % NUM_STEPS;
        
        int prevBar = currentBar;
        currentBar = currentStep / (NUM_STEPS / NUM_PAGES);
        
        // detect bar change
        if(prevBar != currentBar) {
            pageChanged = true;
            if(isFollowMode()) editPage = currentBar;
            
        }
        
        std::vector<SequencerPad*> activePads = getActivePadsAtStep(currentStep);
        
        for (int i = 0; i < activePads.size(); i++) {
            
            SequencerPad *pad = activePads[i];
            
            if( pad->getVelocityState() != VEL_MUTE) {
                ExternalMIDI::Instance()->sendNoteOn((pad->getPosition().y + 32),
                                                     pad->getVelocityState());
            }
            
        }
    }
}

void Sequencer::resetStep() {
    currentStep = 0;
}

int Sequencer::getCurrentStep() {
    return (int)currentStep % 32;
}

bool Sequencer::hasPageChanged() {
    return pageChanged;
}

void Sequencer::resetPageChanged() {
    pageChanged = false;
}

//--------------------------
// Sequencer Timer Methods
//--------------------------

void Sequencer::initTimer(int _timeInterval) {
    
    timeInterval = _timeInterval;
    lastStamp = ofGetElapsedTimeMillis();
}

bool Sequencer::checkTimer() {
    if (ofGetElapsedTimeMillis() - lastStamp > timeInterval) {
        lastStamp = ofGetElapsedTimeMillis();
        return true;
    }
    else return false;
}

//--------------------------
// MIDI Clock Methods
//--------------------------

void Sequencer::start() {
    isRunning = true;
    
    //currentStep = 0;
    //currentBar = 0;
    
    //tick = 0;
    
    incStep();
    
}
void Sequencer::stop() {
    isRunning = false;
    
    tick = 0;
    
    currentStep = 0;
    currentBar = 0;

    editPage = 0;
}

void Sequencer::clockTick() {
    tick = (tick+1) % midiClockDivision;
    
    if (tick >= midiClockDivision - 1) {
        incStep();
    }
}

void Sequencer::incClockDivision() {
    midiClockDivision *= 2;
    
    if(midiClockDivision > 48) midiClockDivision = 48;
}

void Sequencer::decClockDivision() {
    midiClockDivision /= 2;
    
    if(midiClockDivision < 3) midiClockDivision = 3;
}
