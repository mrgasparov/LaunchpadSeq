//
//  Sequencer.h
//  exampleInput
//
//  Created by Pedro Mendes on 10/06/14.
//
//

#ifndef __exampleInput__Sequencer__
#define __exampleInput__Sequencer__

#include <iostream>

#include "ofMain.h"

#include "Launchpad.h"
#include "ExternalMIDI.h"

#include "SequencerPad.h"
#include "SequencerPattern.h"

#include "op_direction_t.h"


class Sequencer {
    
public:

    //--------------------------
    // Sequencer Core Methods
    //--------------------------
    
    static Sequencer* Instance();

    void init();
    void update();
    
    //--------------------------
    // Sequencer Settings Methods
    //--------------------------
    
    void toggleFollowMode();
    bool isFollowMode();
    
    void toggleVelocityMode();
    bool isVelocityMode();
    
    //--------------------------
    // Sequencer Grid Methods
    //--------------------------
    
    void togglePadAtPos(ofPoint _pos);
    pad_colors_t getPadColorAtPos(ofPoint _pos);
    
    ofPoint translatePadPosition(ofPoint _pos);
    
    std::vector<SequencerPad*> getActivePadsAtStep(int _step);
    
    void mutePadLine(int _y);
    void deletePadLine(int _y);
    
    
    void copyPage(op_direction_t _dir);
    
    

    void togglePatternAtPos(ofPoint _pos);
    void copyPatternToPos(ofPoint _pos);
    pad_colors_t getPatternColorAtPos(ofPoint _pos);
    
    //----------------------------
    // Sequencer Edit View Methods
    //----------------------------
    
    void setEditPage(int _page);
    int getEditPage();
    
    void incEditPage();
    void decEditPage();
    
    void setTopTrack(int _track);
    int getTopTrack();
    
    void incTopTrack();
    void decTopTrack();
    
    //--------------------------
    // Sequencer Step Methods
    //--------------------------
    
    void setStepInc(float _stepInc);
    
    void incStep();
    void resetStep();
    
    int getCurrentStep();
    
    bool hasPageChanged();
    void resetPageChanged();
    
    
    //--------------------------
    // Sequencer Timer Methods
    //--------------------------
    
    void initTimer(int _timeInterval);
    bool checkTimer();
    
    //--------------------------
    // MIDI CLock Methods
    //--------------------------
    
    void start();
    void stop();
    
    void clockTick();
    
    void incClockDivision();
    void decClockDivision();
    
private:
    
    //--------------------------
    // Constants
    //--------------------------
    
    const int NUM_STEPS = 32;
    
    const int NUM_TRACKS = 32;
    const int MIN_TOP_TRACK = 0;
    const int MAX_TOP_TRACK = 26; // edit area is 6 x 8, and there are 32 track, the last top track is 26
    
    
    const int NUM_PAGES = 4;
    const int MIN_EDIT_PAGE = 0;
    const int MAX_EDIT_PAGE = 3;
    
    //-------------------------------
    // Sequencer Core Private Methods
    //-------------------------------
    
    // Private so that it can  not be called
    //          this is a trick to initialize the vector
    Sequencer() :
    patternBank(8, std::vector<SequencerPattern>(8, SequencerPattern()))
    {};
    Sequencer(Sequencer const&);            // copy constructor is private
    Sequencer& operator=(Sequencer const&){};  // assignment operator is private
    static Sequencer* m_pInstance;

    //--------------------------
    // Sequencer Settings Methods
    //--------------------------
    
    bool followMode = false;
    bool velocityMode = false;
    
    //--------------------------
    // Sequencer Grid Attributes
    //--------------------------
    
    // 32 track x 32 step grid used to store whole pattern
    //std::vector<std::vector<SequencerPad> > sequencerPadMatrix;
    
    ofPoint prevPattern = ofPoint(0,0);
    ofPoint currentPattern = ofPoint(0,0);
    
    std::vector<std::vector<SequencerPattern> > patternBank;// = SequencerPattern();
    
    //-------------------------------
    // Sequencer Edit View Attributes
    //-------------------------------
    
    int editPage = 0;
    int topTrack = 0;
    
    //--------------------------
    // Sequencer Step Attributes
    //--------------------------
    
    float stepInc = 1;
    
    float currentStep = 0;
    int currentBar = 0;
    
    bool pageChanged = false;
    
    //--------------------------
    // Sequencer Timer Attributes
    //--------------------------
    
    int timeInterval = 260;
    double lastStamp = 0;
    
    //--------------------------
    // MIDI CLock Attributes
    //--------------------------
    
    bool isRunning = false;
    
    int tick = 0;
    
    int midiClockDivision = 6;

};




#endif /* defined(__exampleInput__Sequencer__) */
