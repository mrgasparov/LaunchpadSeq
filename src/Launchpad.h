//
//  Launchpad.h
//  exampleInput
//
//  Created by Pedro Mendes on 10/06/14.
//
//

#ifndef __exampleInput__Launchpad__
#define __exampleInput__Launchpad__

#include <iostream>

#include "ofMain.h"
#include "ofxMidi.h"

#include "Sequencer.h"
#include "LaunchpadPad.h"

#include "edit_mode_t.h"

class Launchpad : public ofxMidiListener{
    
public:
    
    static Launchpad* Instance();
    
    void init(string _inPort, string _outPort);
    void close();
    
    void update();
    
    void toggleEditMode(edit_mode_t _mode);
    bool isEditMode(edit_mode_t _mode);
    
    /*void toggleDeleteLineMode();
    bool isDeleteLineMode();
    
    void toggleMuteLineMode();
    bool isMuteLineMode();*/
    
    //-------------------------------
    // Display
    //-------------------------------
    
    void updateMatrix();
    
    void displayMatrix();
    void displayButtons();
    
private:
    
    //--------------------------
    // Constants
    //--------------------------
    
    const int MIDI_OUT_CH = 1;
    
    const int MATRIX_WIDTH = 8;
    const int MATRIX_HEIGHT = 8;
    
    const int GRID_WIDTH = 8;
    const int GRID_HEIGHT = 6;
    const int GRID_START_LINE = 2;
    const int GRID_START_NOTE_XY = 32;
    const int GRID_LINE_MULT_XY = 16;
    
    //-------------------------------
    // Sequencer Singleton Methods
    //-------------------------------
    
    Launchpad():
        topButtonsMatrix(MATRIX_WIDTH, LaunchpadPad()),
        rightButtonsMatrix(MATRIX_HEIGHT, LaunchpadPad()),
        padMatrix(MATRIX_WIDTH, std::vector<LaunchpadPad>(MATRIX_HEIGHT, LaunchpadPad()))
    {};

    Launchpad(Launchpad const&){};             // copy constructor is private
    Launchpad& operator=(Launchpad const&){};  // assignment operator is private
    static Launchpad* m_pInstance;
    
    //--------------------------
    // Sequencer Settings Methods
    //--------------------------
    
    /*bool deleteLineMode = false;
    bool muteLineMode = false;*/
    
    std::map<edit_mode_t, bool> editModeMap;
    
    //-------------------------------
    // MIDI IN
    //-------------------------------
    
    ofxMidiIn midiIn;
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    void processNoteOn(int _pitch, int _vel, double _delta);
    void processCtlChange(int _ctl, int _val, double _delta);
    
    //-------------------------------
    // MIDI OUT
    //-------------------------------
    
    ofxMidiOut midiOut;
	int channel;
    
    void printColorToPad(int _note, int _color);
    
    //-------------------------------
    // Display
    //-------------------------------
    
    // 1 x 8 matrix representing top buttons
    std::vector<LaunchpadPad> topButtonsMatrix;
    
    // 1 x 8 matrix representing left buttons
    std::vector<LaunchpadPad> rightButtonsMatrix;
    
    // 8 x 8 matrix representing square pads
    std::vector<std::vector<LaunchpadPad> > padMatrix;
    
};

#endif /* defined(__exampleInput__Launchpad__) */
