#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <PLab_ZumoMotors.h>

#define QTR_THRESHOLD  1800

// global speed variables
int leftSpeed;
int rightSpeed;

ZumoMotors motors;
PLab_ZumoMotors pLabMotors;
Pushbutton button(ZUMO_BUTTON);
 
#define NUM_SENSORS 6
unsigned int sensorValues[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

void setup(){
  sensors.init();
  button.waitForButton();
}

void loop(){
  retreat();
}

// check if the leftmost sensor is detecting line
boolean lineDetectLeft() {
  if (sensorValues[0] > QTR_THRESHOLD) {
   return true; 
  }
  return false;
}

// check if the rightmost sensor is detecting line
boolean lineDetectRight() {
  if (sensorValues[5] > QTR_THRESHOLD) {
   return true; 
  }
  return false;
}

// check if any of the six sensors are detecting line
boolean lineDetect() {
  for (int sensorValue: sensorValues) {
    if (sensorValue > QTR_THRESHOLD) {
      return true;    
  }
  return false;
 }
}

void updateSpeeds(int left, int right) {
  leftSpeed = left;
  rightSpeed = right;
  motors.setSpeeds(leftSpeed, rightSpeed);
}

void retreat() {
  sensors.read(sensorValues);
  // if line is detected on both the leftmost and rightmost sensor, start turning around
  if (lineDetectLeft() && lineDetectRight()) {
    updateSpeeds(-300, 300)
    break;
  } else if (lineDetectLeft()) {
    // turn right
    updateSpeeds(300, 200);
  } else if (lineDetectRight()) {
    // turn left
    updateSpeeds(200, 300);
  }
}
