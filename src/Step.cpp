//
//  Step.cpp
//  sequencer
//
//  Created by Andreu Grimalt-Reynes on 03/01/2015.
//
//

#include "Step.h"

Step::Step(int position){
    this->position=position;
}
Step::Step(){
    
}

void Step::setOn(bool on){
    this->on=on;
}

bool Step::getOn(){
    return on;
}

bool Step::getPlay(){
    return play;
}

void Step::setPlay(bool play){
    this->play=play;
}


int Step::getPosition(){
    return position;
}

void Step::toggleOn(){
    if(on){
        on=false;
    }else{
        on=true;
    }
}


Sequence::Sequence(int sequenceLength,int stepSize,maxiEnvelope* envelope,int position){
    this->sequenceLength=sequenceLength;
    this->stepSize=stepSize;
    this->envelope=envelope;
    this->position=position;
    steps=(Step*)malloc(sequenceLength * sizeof(Step));
    for(int i=0; i<sequenceLength; i++){
        steps[i]=*new Step(i);
    }
}
Sequence::Sequence(){
    
}

Step* Sequence::getSequence(){
    return steps;
}

int Sequence::getSequenceLength(){
    return sequenceLength;
}

int Sequence::getStepSize(){
    return stepSize;
}

int Sequence::getCurrentStep(){
    return currentStep;
}
int Sequence::setCurrentStep(int theStep){
    currentStep=theStep;
}

maxiEnvelope* Sequence::getEnvelope(){
    return envelope;
}

int Sequence::getPosition(){
    return position;
}