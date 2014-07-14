//
//  ExternalMIDI.cpp
//  exampleInput
//
//  Created by Pedro Mendes on 10/06/14.
//
//

#include "ExternalMIDI.h"

// Global static pointer used to ensure a single instance of the class.
ExternalMIDI* ExternalMIDI::m_pInstance = NULL;

/** This function is called to create an instance of the class.
 Calling the constructor publicly is not allowed. The constructor
 is private and is only called by this Instance function.
 */

ExternalMIDI* ExternalMIDI::Instance()
{
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new ExternalMIDI;
    
    return m_pInstance;
}



void ExternalMIDI::init(string _inPort, string _outPort){
    
    // INIT MIDI INPUT
    midiIn.openPort(_inPort);
    // don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
    midiIn.ignoreTypes(false, false, false);
	midiIn.addListener(this);
    
    // INIT MIDI OUTPUT
    
    midiOut.openPort(_outPort);
	channel = 1;
}

void ExternalMIDI::init(string _outPort){
    
    
    // INIT MIDI OUTPUT
    
    midiOut.openPort(_outPort);
	channel = 1;
}

void ExternalMIDI::close(){
    
    // clean up
}

void ExternalMIDI::update(){

}

void ExternalMIDI::newMidiMessage(ofxMidiMessage& msg) {
    
    MidiStatus status = msg.status;
    
    switch (status){
            
        case MIDI_TIME_CLOCK: {
            //cout << "TIME CLOCK" << endl;
            
            Sequencer::Instance()->clockTick();
            break;
        }
            
        case MIDI_START: {
            //cout << "TIME CLOCK" << endl;
            
            Sequencer::Instance()->start();
            break;
        }
            
        case MIDI_STOP: {
            //cout << "TIME CLOCK" << endl;
            
            Sequencer::Instance()->stop();
            break;
        }
            
            
        default: break;
    }
}


void ExternalMIDI::sendNoteOn(int _pitch, int _vel) {
    
    //cout << "Sending MIDI note: " << _pitch << endl;
    midiOut.sendNoteOn(channel, _pitch,  _vel);
    midiOut.sendNoteOff(channel, _pitch,  _vel);
}