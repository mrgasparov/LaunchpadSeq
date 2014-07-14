#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
    // setting frame rate is extremely important! otherwise cpu peaks when window is on background
    ofSetFrameRate(60);
    
	ofBackground(255, 255, 255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
    // this is our buffer to stroe the text data
    ofBuffer buffer = ofBufferFromFile("interfaces.txt");
    
    if(buffer.size()) {
        
        // we now keep grabbing the next line
        // until we reach the end of the file
        while(buffer.isLastLine() == false) {
            
            // move on to the next line
            string line = buffer.getNextLine();
            
            // copy the line to draw later
            // make sure its not a empty line
            if(line.empty() == false) {
                midiInterfaceNames.push_back(line);
            }
            
            // print out the line
            cout << line << endl;
            
        }
    }

    
    Sequencer::Instance()->init();
    
    Launchpad::Instance()->init(midiInterfaceNames[0], midiInterfaceNames[1]); // "Launchpad S", "Launchpad S");
    ExternalMIDI::Instance()->init(midiInterfaceNames[2], midiInterfaceNames[3]); //"IAC Driver Bus 1", "IAC Driver Bus 1");
}

//--------------------------------------------------------------
void testApp::update() {
    
    Sequencer::Instance()->update();
    Launchpad::Instance()->update();
}

//--------------------------------------------------------------
void testApp::draw() {
    ofBackground(0);
    ofDrawBitmapString("Launchpad Seq v0.11\nmrgasparov@gmail.com", 50, 50);
    
    stringstream ss2;
    ss2 << Sequencer::Instance()->getCurrentStep();
    string currentStep = ss2.str();
    
    ofDrawBitmapString(currentStep, 50, 80);
}

//--------------------------------------------------------------
void testApp::exit() {

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mouseReleased() {
}
