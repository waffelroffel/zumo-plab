#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <PLabBTSerial.h>
#include <Pushbutton.h>
#include <NewPing.h>

// DEFINE PINS
#define echoPinRight 2 // Right Echo Pin
#define trigPinRight 3 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft A0 // Left Trigger Pin


// DEFINE CONSTANTS
const int MAX_SPEED = 400;
#define maxDistance 50

// DEFINE STATES
int state;
#define SEARCH 0;
#define ATTACK 1;
#define DEFENCE 2;
#define RETURN 3;

// Variables for distance measurements
NewPing rightSonar(trigPinRight, echoPinRight, maxDistance);
NewPing leftSonar(trigPinLeft, echoPinLeft, maxDistance);

// Global variables
int leftDistance; //Distances to enemies
int rightDistance;
int leftSpeed; // Speeds on the wheels
int rightSpeed;
int previousLeftSpeed;
int previousRightSpeed;
int side; //truffet side

void setup() {
    // SETUP AND MANOUVER TO MIDDLE
    sensors.init();
    motors.setSpeeds(400,120);
    delay(750);
    motors.setSpeeds(0,0);
}

void loop() {
    leftDistance = getDistance(leftSonar);
    rightDistance = getDistance(rightSonar);
    // **ALL** SENSOR INPUT AND CALCULATIONS

    // DECIDE STATE BASED ON SENSOR INPUT

    // SWITCH-CASE
    switch (state) {
        case SEARCH:
            searchMode();
            break;
        case ATTACK:
            // ATTACK LOGIC
            break;
        case DEFENCE:
            evasion(side);
            // DEFENCE LOGIC
            break;
        case RETURN:
            // RETURN LOGIC
            break;
        }
    }

}

void evasion(int side){
  switch(side){
    case 1: motors.updateSpeeds(-400,-100,500,2); break; //front
    case 2: motors.updateSpeeds(400,100,500,2); break; //back
    case 3: motors.updateSpeeds(400,400,500,2); break; //left
    case 4: motors.updateSpeeds(400,400,500,2); break; //right
  }
}

void updateSpeeds(int newleftSpeed, int newRightSpeed){
  previousLeftSpeed = leftSpeed;
  previousRightSpeed = rightSpeed;
  leftSpeed = newleftSpeed;
  rightSpeed = newRightSpeed;
  motors.setSpeeds(leftSpeed, rightSpeed);
}

long getDistance(NewPing sonar){
  //Serial.println(sonar.ping_cm());
  return sonar.ping_cm();
}

void searchMode(){
  //btSerial.println("Running searchMode");
  motors.setSpeeds(400,-400);
}

void retreat() {
  // global?
  sensors.read(sensorValues);
  // if line is detected on both the leftmost and rightmost sensor, start turning around
  if ((sensorValues[0] > QTR_THRESHOLD) && (sensorValues[5] > QTR_THRESHOLD))) {
    updateSpeeds(-300, 300)
    break;
  } else if (sensorValues[0] > QTR_THRESHOLD) {
    // turn right
    updateSpeeds(300, 200);
  } else if (sensorValues[5] > QTR_THRESHOLD) {
    // turn left
    updateSpeeds(200, 300);
  }
}
