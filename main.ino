
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <PLabBTSerial.h>
#include <Pushbutton.h>



ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

#define echoPinRight 2 // Right Echo Pin
#define trigPinRight 3 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft 6 // Left Trigger Pin



const int MAX_SPEED = 400;
const unsigned long DEFENSE_MODE_TIME = 3000 // ms

const int REST = 0;
const int SEARCH = 1;
const int ATTACK = 2;
const int DEFENCE = 3;

// variabler for motor
int lastError = 0;



//Variabler for avstandsmåling
long duration, distance;
int number = 3;
int between = 3;


// variabler for tilstand
int lastState;
int state;
// tilstander: 
// 0 = før start
// 1 = søk
// 2 = angrep
// 3 = forsvar







void setup() {
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  
  button.waitForButton();
  motors.setSpeeds(400,-400);
  searchMode();
  lastState = REST;
  state = REST;
  button.waitForButton();
  state = SEARCH;
  
}

void loop() {
  // endre tilstand
  if (state == SEARCH && hasFoundTarget()) {
    state = ATTACK;
  }
  else if (state == DEFENCE && (milis() - defenceModeStart > DEFENSE_MODE_TIME) {
    state = SEARCH;
  }
  else if (state == SEARCH && detectsImpact()) {
    state = DEFENCE;
  }

  
  // sammenligne tilstander, og sett bevegelser
  if (state == SEARCH && state != lastState) {
    setSearchMode();
  }
  else if (state == DEFENCE && state != lastState) {
    setDefenceModeRight();
    unsigned long defenceModeStart = milis();
  }
  else if (state == ATTACK && state != lastSTate) {
    setAttackMode();
  }

  // logikk for hver modus
  

  
  
  lastState = state;
}

void setSearchMode() {
  motors.setSpeeds(400,-400);
}

void setDefenceModeRight() {
  motors.setSpeeds(400, 200);
}

void boolean detectsImpact() {
  
}

void boolean hasFoundTarget() {
  if (getDistance(trigPinLeft, echoPinLeft) < 20) {
    return true;
  }
  return false;
}

long getDistance(int trig,int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;
  return distance;
}
