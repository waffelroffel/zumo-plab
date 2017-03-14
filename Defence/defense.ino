#include <ZumoMotors.h>
#include <Pushbutton.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

void setup(){
    button.waitForButton();
}

void loop(){
}

void defenseMode(){
    if(something){
        updateSpeed(400,200);
    }else{
        updateSpeed(200,400);
    }
}

void evade(){
    int state;
    switch(state){
        case 1: updateSpeeds(400,-400); break;
        case 2: updateSpeeds(-400,400); break;
        case 3: updateSpeeds(400,200); break;
        case 4: updateSpeeds(200,400); break;
        default: break;
}
