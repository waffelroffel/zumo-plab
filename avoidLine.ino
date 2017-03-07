#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

#define QTR_THRESHOLD  1800

#define TURN_SPEED        400
#define FORWARD_SPEED     200
#define TURN_DURATION     140 // ms
 
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

void setup(){
  sensors.init();
  button.waitForButton();
}

void loop(){
  avoidLine();
}

void avoidLine(){
  sensors.read(sensor_values);
  if(sensor_values[0] > QTR_THRESHOLD){
    // if leftmost sensor detects line, turn to the right
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(70);
  }else if(sensor_values[5] > QTR_THRESHOLD){
    // if rightmost sensor detects line, turn to the left
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(70);
  }else{
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}

