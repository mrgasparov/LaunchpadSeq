//
//  Launchpad.cpp
//  exampleInput
//
//  Created by Pedro Mendes on 10/06/14.
//
//

#include "Launchpad.h"



// Global static pointer used to ensure a single instance of the class.
Launchpad* Launchpad::m_pInstance = NULL;

/** This function is called to create an instance of the class.
 Calling the constructor publicly is not allowed. The constructor
 is private and is only called by this Instance function.
 */

Launchpad* Launchpad::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new Launchpad;
    
    return m_pInstance;
}



void Launchpad::init(string _inPort, string _outPort){
    
    // INIT RIGHT BUTTONS MATRIX
    
        for(int y = 0; y < MATRIX_HEIGHT; y++) {
            LaunchpadPad *pad = &(rightButtonsMatrix[y]);
            
            pad->setPadColor(OFF);
            pad->setPosition(ofPoint(0,y));
            pad->setAddressXYMode(8 + (y * GRID_LINE_MULT_XY));
            pad->setAddressDrumMode(-1); // have to calculate the drum address
        }
    
    // INIT PAD MATRIX
    
    for(int y = 0; y < MATRIX_WIDTH; y++) {
        for(int x = 0; x < MATRIX_HEIGHT; x++) {
            LaunchpadPad *pad = &(padMatrix[x][y]);
            
            pad->setPadColor(OFF);
            pad->setPosition(ofPoint(x,y));
            pad->setAddressXYMode(x + (y * GRID_LINE_MULT_XY));
            pad->setAddressDrumMode(-1); // have to calculate the drum address
        }
    }
    
    // INIT EDIT MODE MAP
    
    editModeMap[LINE_DELETE] = false;
    editModeMap[LINE_MUTE] = false;
    editModeMap[LINE_COPY] = false;
    
    editModeMap[PAGE_DELETE] = false;
    editModeMap[PAGE_COPY] = false;

    editModeMap[PATTERN_DELETE] = false;
    editModeMap[PATTERN_COPY] = false;
    
    
    // INIT MIDI INPUT
    
    std::vector<string> midiInPortList = midiIn.getPortList();
	midiIn.listPorts();

    midiIn.openPort(_inPort);
	midiIn.addListener(this);
	//midiIn.setVerbose(true);
    
    
    // INIT MIDI OUTPUT
    std::vector<string> midiOutPortList = midiOut.getPortList();
    midiOut.listPorts();
    midiOut.openPort(_outPort);
	channel = 1;

    
    displayMatrix();
}

void Launchpad::close(){
    
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
}

void Launchpad::update(){
    
}

void Launchpad::toggleEditMode(edit_mode_t _mode) {
    editModeMap.at(_mode) = !(editModeMap.at(_mode));
}

bool Launchpad::isEditMode(edit_mode_t _mode) {
    return editModeMap.at(_mode);
}


/*void Launchpad::toggleDeleteLineMode() {
    deleteLineMode = !deleteLineMode;
}

bool Launchpad::isEditMode(LINE_DELETE) {
    return deleteLineMode;
}

void Launchpad::toggleMuteLineMode() {
    muteLineMode = !muteLineMode;
}

bool Launchpad::isEditMode(LINE_MUTE) {
    return muteLineMode;
}*/



void Launchpad::updateMatrix(){
    
    // update grid
    
    for(int y = 0; y < MATRIX_HEIGHT; y++) {
        for(int x = 0; x < MATRIX_WIDTH; x++) {
            
            LaunchpadPad *pad = &(padMatrix[x][y]);
            
            // top locator bar
            if(y == 0) {
                
                
                // edit page
                int editPage = Sequencer::Instance()->getEditPage();
                
                if((x >= editPage*2) && (x <= ((editPage*2)+1))){
                    
                    pad->setPadColor(ORANGE_FULL);
                    
                    // scrolling locator
                    int stepPos = Sequencer::Instance()->getCurrentStep();
                    int scaledPos = stepPos / 4.f;
                    
                    if(scaledPos == x) {
                        pad->setPadColor(RED_FULL);
                    }
                    
                }
                else {
                    pad->setPadColor(OFF);
                    
                    // scrolling locator
                    int stepPos = Sequencer::Instance()->getCurrentStep();
                    int scaledPos = stepPos / 4.f;
                    
                    if(scaledPos == x) {
                        pad->setPadColor(RED_FULL);
                    }
                }
                
            }
            // bottom locator bar
            else if(y == 1) {
                int stepPos = Sequencer::Instance()->getCurrentStep();
                int stepAtPage = stepPos / 8.f;
                
                if (stepAtPage == Sequencer::Instance()->getEditPage()) {
                    int modedStepPos = stepPos % 8;
                    
                    if(modedStepPos == x) {
                        pad->setPadColor(AMBER_FULL);
                    }
                    else {
                        pad->setPadColor(OFF);
                    }
                }
                else {
                    pad->setPadColor(OFF);
                }
            }
            // extract color values from sequencer and transpose to the 6x8 sequencer grid
            else if(y >= GRID_START_LINE) {
                ofPoint pos = ofPoint(x, y-GRID_START_LINE);
                pad_colors_t color = Sequencer::Instance()->getPadColorAtPos(pos);
                
                pad->setPadColor(color);
            }
        }
    }
}

void Launchpad::displayMatrix(){
    
    // display matrix
    
    for(int y = 0; y < MATRIX_HEIGHT; y++) {
        for(int x = 0; x < MATRIX_WIDTH; x++) {
            
            LaunchpadPad *pad = &(padMatrix[x][y]);
            
            if(pad->colorChanged()) {
                pad->printColor(); // only being used to equal color and prevColor on the pad object
                printColorToPad(pad->getAddressXYMode(), pad->getPadColor());
            }

        }
    }
}

void Launchpad::displayButtons(){

    for(int y = 0; y < MATRIX_HEIGHT; y++) {
        LaunchpadPad *pad = &(rightButtonsMatrix[y]);
        
        if(pad->colorChanged()) {
            pad->printColor(); // only being used to equal color and prevColor on the pad object
            printColorToPad(pad->getAddressXYMode(), pad->getPadColor());
        }
    }
}

void Launchpad::printColorToPad(int _note, int _color) {
    midiOut.sendNoteOn(MIDI_OUT_CH, _note,  _color);
}


/*int Launchpad::getAddressFromGridPos(ofPoint _pos) {
    
    int note = (GRID_START_NOTE_XY + (_pos.y * GRID_LINE_MULT_XY)) + _pos.x;
    
    return note;
}*/


void Launchpad::newMidiMessage(ofxMidiMessage& msg) {

    MidiStatus status = msg.status;
    
    switch (status){
            
        case MIDI_NOTE_ON: {
            processNoteOn(msg.pitch, msg.velocity, msg.deltatime);
            
            break;
        }
        case MIDI_CONTROL_CHANGE: {
            processCtlChange(msg.control, msg.value, msg.deltatime);
            break;
        }
        
        default: break;
    }
}

///

void Launchpad::processNoteOn(int _pitch, int _vel, double _delta) {

        switch (_pitch) {
                
                // vol
            case 8: {
                toggleEditMode(LINE_MUTE);
                break;
            }
                // pan
            case 24: {
                toggleEditMode(LINE_DELETE);
                break;
            }   // snd A
            case 40: {
                if(_vel == 127) {
                    if(isEditMode(LINE_MUTE)) Sequencer::Instance()->mutePadLine(0);
                    else if(isEditMode(LINE_DELETE)) Sequencer::Instance()->deletePadLine(0);
                    else {
                        Sequencer::Instance()->copyPage(LEFT);
                    }
                }
                break;
            }
                // snd B
            case 56: {
                if(_vel == 127) {
                    if(isEditMode(LINE_MUTE)) Sequencer::Instance()->mutePadLine(1);
                    else if(isEditMode(LINE_DELETE)) Sequencer::Instance()->deletePadLine(1);
                    else {
                        Sequencer::Instance()->copyPage(RIGHT);
                    }
                }
                break;
            }
                // stop
            case 72: {
                if(_vel == 127) {
                    if(isEditMode(LINE_MUTE)) Sequencer::Instance()->mutePadLine(2);
                    else if(isEditMode(LINE_DELETE)) Sequencer::Instance()->deletePadLine(2);
                    else {
                        Sequencer::Instance()->decClockDivision();
                    }
                }
                break;
            }
                // trk on
            case 88: {
                if(_vel == 127) {
                    if(isEditMode(LINE_MUTE)) Sequencer::Instance()->mutePadLine(3);
                    else if(isEditMode(LINE_DELETE)) Sequencer::Instance()->deletePadLine(3);
                    else {
                        Sequencer::Instance()->incClockDivision();
                    }
                }
                break;
            }
                // solo
            case 104: {
                if(_vel == 127) {
                    if(isEditMode(LINE_MUTE)) Sequencer::Instance()->mutePadLine(4);
                    else if(isEditMode(LINE_DELETE)) Sequencer::Instance()->deletePadLine(4);
                    else {
                        Sequencer::Instance()->toggleVelocityMode();
                        
                        // toggle button color
                        LaunchpadPad *pad = &(rightButtonsMatrix[6]);
                        pad->togglePadColor();
                    }
                }
                
                break;
            }
                // arm
            case 120: {
                if(_vel == 127) {
                    if(isEditMode(LINE_MUTE)) Sequencer::Instance()->mutePadLine(5);
                    else if(isEditMode(LINE_DELETE)) Sequencer::Instance()->deletePadLine(5);
                    else {
                        Sequencer::Instance()->toggleFollowMode();
                        
                        // toggle button color
                        LaunchpadPad *pad = &(rightButtonsMatrix[7]);
                        pad->togglePadColor();
                        
                    }
                }
                break;
            }
                
                
                // grid
            default: {
                
                // only process on press?
                if(_vel == 127) {
                    
                    int x = _pitch % 8;
                    int y = _pitch / 16.f;
                    
                    if(y >= 2) {
                        
                        y = y-2;
                        
                        
                        std::stringstream logOut;
                        logOut << "y: " << y << " > ";
                        logOut << "x: " << x;
                        cout << logOut.str() << endl;
                        
                        
                        Sequencer::Instance()->togglePadAtPos(ofPoint(x,y));
                    }
                    
                    
                }
                
                break;
            }
        }
}


void Launchpad::processCtlChange(int _ctl, int _val, double _delta) {
    
        switch (_ctl) {
                
                // up
            case 104: {
                if(_val == 127) {
                    
                    Sequencer::Instance()->incTopTrack();
                }
                
                break;
            }
                // down
            case 105: {
                if(_val == 127) {
                    
                    Sequencer::Instance()->decTopTrack();
                }
                
                break;
            }
                // left
            case 106: {
                if(_val == 127) {
                    
                    if (isEditMode(PAGE_COPY)) Sequencer::Instance()->copyPage(LEFT);
                        else Sequencer::Instance()->decEditPage();
                }
                
                break;
            }
                // right
            case 107: {
                if(_val == 127) {
                    
                    if (isEditMode(PAGE_COPY)) Sequencer::Instance()->copyPage(RIGHT);
                    else Sequencer::Instance()->incEditPage();
                }
                break;
            }
                // session
            case 108: {
                
                break;
            }
                // user 1
            case 109: {
                break;
            }
                // user 2
            case 110: {
                break;
            }
                // mixer
            case 111: {
                toggleEditMode(PAGE_COPY);
                break;
            }
                
            default: {
                
                break;
            }
        }
}