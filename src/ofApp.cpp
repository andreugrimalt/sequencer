#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    for(int i=0; i<15; i++){
        sequenceArray[i]=Sequence((int)ofRandom(25,44),30,&envelopes[i],30*i+i);
        stringstream tempPath;
        tempPath << i << ".wav";
        string path=tempPath.str();
        //cout<<path<<"\n";
        // samples from here: http://smd-records.com/tr808/?page_id=14
        samples[i].load(ofToDataPath(path));
        samples[i].getLength();
    }
    
    sampleRate=44100;
    initialBufferSize=256;
    
    // GUI
    gui.setup();
    gui.setPosition(1280, 10);
    start.addListener(this,&ofApp::startButtonPressed);
    stop.addListener(this,&ofApp::stopButtonPressed);
    reset.addListener(this,&ofApp::resetButtonPressed);
    gui.add(rate.setup( "rate", 5, 1, 12 ));
    gui.add(start.setup("start"));
    gui.add(reset.setup("reset"));
    gui.add(stop.setup("stop"));
    
    ofSoundStreamSetup(2,0, this, sampleRate, initialBufferSize, 4);
}

void ofApp::startButtonPressed(){
    run=true;
}
void ofApp::stopButtonPressed(){
    run=false;
}

void ofApp::resetButtonPressed(){
    resetBool=true;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    for(int j=0; j<sizeof(sequenceArray)/sizeof(sequenceArray[0]);j++){
        for(int i=0; i<sequenceArray[j].getSequenceLength(); i++){
            if(sequenceArray[j].getSequence()[i].getOn()){
                ofSetColor(200,200,255);
            }
            if(!sequenceArray[j].getSequence()[i].getOn()){
                ofSetColor(0,0,100);
            }
            if(sequenceArray[j].getSequence()[i].getPlay()){
                ofSetColor(200,255,255);
            }
            if(!sequenceArray[j].getSequence()[i].getPlay()){
                // ofSetColor(0);
            }
            ofRect(i+sequenceArray[j].getSequence()[i].getPosition()*sequenceArray[j].getStepSize(),sequenceArray[j].getPosition(),sequenceArray[j].getStepSize(),sequenceArray[j].getStepSize());
        }
    }

    gui.draw();
}

void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){

    for (int i = 0; i < bufferSize; i++){
        if(run){
            //there's a bug, rate=8 & rate=11 don't work...
            if(rate==8){
                rate=7;
            }
            if(rate==11){
                rate=10;
            }
           // main phasor that controls the rate
           mainPhasorValue=phasor.phasor((int)rate,0,1);
        }
        // mainPhasorValue=1 -> move one step forward
        if(mainPhasorValue==1){
            
            for(int j=0; j<sizeof(sequenceArray)/sizeof(sequenceArray[0]);j++){
                for(int i=0; i<sequenceArray[j].getSequenceLength();i++){
                    // turn off previous lighted steps
                    sequenceArray[j].getSequence()[i].setPlay(false);
                }
                // if reset is pressed -> start the sequence from the begginging
                if(resetBool){
                    sequenceArray[j].setCurrentStep(0);
                    if(j==sizeof(sequenceArray)/sizeof(sequenceArray[0])-1){
                        resetBool=false;
                    }
                }
                // wrap sequence
                sequenceArray[j].setCurrentStep(sequenceArray[j].getCurrentStep()%sequenceArray[j].getSequenceLength());
                //cout<<sequenceArray[j].getCurrentStep()<<"\n";
                
                // light the current step
                sequenceArray[j].getSequence()[sequenceArray[j].getCurrentStep()].setPlay(true);
                
                // if the step is on -> trigger the envelope to play the sample
                if(sequenceArray[j].getSequence()[sequenceArray[j].getCurrentStep()].getOn()){
                    // reset the sample
                    samples[j].reset();
                    // triger the sample
                    sequenceArray[j].getEnvelope()->trigger(0,1);
                }
                // current step is next step
                sequenceArray[j].setCurrentStep(sequenceArray[j].getCurrentStep()+1);
            }
        }
        
        // add all the samples together
        for(int j=0; j<sizeof(sequenceArray)/sizeof(sequenceArray[0]);j++){
            wave+=sequenceArray[j].getEnvelope()->exponential(2000)*samples[j].play(1,0,samples[j].length);
        }
        // normalise
        wave/=16;

        output[i*nChannels] = wave; 
        output[i*nChannels+1] = wave;
    }
}

void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels){
    
    
    /* You can just grab this input and stick it in a double, then use it above to create output*/
    
    for (int i = 0; i < bufferSize; i++){
        
        /* you can also grab the data out of the arrays*/
        
        lAudioIn[i] = input[i*2];
        rAudioIn[i] = input[i*2+1];
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for(int j=0; j<sizeof(sequenceArray)/sizeof(sequenceArray[0]);j++){
        for(int i=0; i<sequenceArray[j].getSequenceLength();i++){
            if(sequenceArray[j].getSequence()[i].getPosition()*sequenceArray[j].getStepSize()+i<x&&x<sequenceArray[j].getSequence()[i].getPosition()*sequenceArray[j].getStepSize()+sequenceArray[j].getStepSize()+i&&sequenceArray[j].getPosition()<y&&y<sequenceArray[j].getPosition()+sequenceArray[j].getStepSize()){
                sequenceArray[j].getSequence()[i].setOn(true);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    for(int j=0; j<sizeof(sequenceArray)/sizeof(sequenceArray[0]);j++){
        for(int i=0; i<sequenceArray[j].getSequenceLength();i++){
            if(sequenceArray[j].getSequence()[i].getPosition()*sequenceArray[j].getStepSize()+i<x&&x<sequenceArray[j].getSequence()[i].getPosition()*sequenceArray[j].getStepSize()+sequenceArray[j].getStepSize()+i&&sequenceArray[j].getPosition()<y&&y<sequenceArray[j].getPosition()+sequenceArray[j].getStepSize()){
                sequenceArray[j].getSequence()[i].toggleOn();
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
