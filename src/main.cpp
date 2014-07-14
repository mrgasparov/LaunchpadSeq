#include "ofMain.h"
#include "testApp.h"

int main(){
	ofSetupOpenGL(280, 140, OF_WINDOW);
	ofRunApp(new testApp());
}
