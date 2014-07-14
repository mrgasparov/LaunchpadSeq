//
//  ExternalMIDI.h
//  exampleInput
//
//  Created by Pedro Mendes on 10/06/14.
//
//

#ifndef __exampleInput__ExternalMIDI__
#define __exampleInput__ExternalMIDI__

#include <iostream>

#include "ofMain.h"
#include "ofxMidi.h"

#include "Sequencer.h"

class ExternalMIDI : public ofxMidiListener{
    
public:
    
    static ExternalMIDI* Instance();
    
    void init(string _outPort);
    void init(string _inPort, string _outPort);
    void close();
    
    void update();
    
    
    void sendNoteOn(int _pitch, int _vel);

private:
    
    ExternalMIDI(){};  // Private so that it can  not be called
    ExternalMIDI(ExternalMIDI const&){};             // copy constructor is private
    ExternalMIDI& operator=(ExternalMIDI const&){};  // assignment operator is private
    static ExternalMIDI* m_pInstance;
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
	
	ofxMidiIn midiIn;
    
    //------------------
    
    ofxMidiOut midiOut;
	int channel;
    
};

#endif /* defined(__exampleInput__ExternalMIDI__) */
