#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
#include "Step.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
    void audioReceived 	(float * input, int bufferSize, int nChannels); /* input method */
    
    float 	* lAudioOut; /* outputs */
    float   * rAudioOut;
    
    float * lAudioIn; /* inputs */
    float * rAudioIn;
    
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
    
    double wave,outputs[2];

    maxiSample samples[20];
    maxiOsc phasor;
    maxiEnvelope envelopes[20];
    float mainPhasorValue;
    
    Sequence sequenceArray[15];
    bool run=false;
    bool resetBool=false;
    
    ofxButton reset;
    ofxButton start;
    ofxButton stop;
    ofxIntSlider rate;
    ofxPanel gui;
    
    void startButtonPressed();
    void stopButtonPressed();
    void resetButtonPressed();
};
