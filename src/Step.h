

#ifndef __sequencer__Step__
#define __sequencer__Step__

#include <stdio.h>
#include <cstdlib>
#include "ofxMaxim.h"
class Step{
    public:
        Step(int position);
        Step();
        void setOn(bool on);
        bool getOn();
        void setPosition(int position);
        int getPosition();
        int getSize();
        void toggleOn();
        bool getPlay();
        void setPlay(bool play);
    private:
        int position;
        bool on=false;
        bool play=false;
};

class Sequence{
    public:
        Sequence(int sequenceLength,int stepSize,maxiEnvelope* envelope,int position);
        Sequence();
        Step* getSequence();
        int getSequenceLength();
        int getStepSize();
        int getCurrentStep();
        int setCurrentStep(int theStep);
        maxiEnvelope* getEnvelope();
        int getPosition();
    
    private:
        Step* steps;
        int sequenceLength;
        int stepSize;
        int currentStep=0;
        maxiEnvelope* envelope;
        int position;
};

#endif /* defined(__sequencer__Step__) */
