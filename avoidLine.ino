#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>

#define QTR_THRESHOLD  100

#define TURN_SPEED        400
#define FORWARD_SPEED     200
#define TURN_DURATION     160
 
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

void setup(){
  sensors.init();
  button.waitForButton();
  delay(1000);
  for(int i = 0; i < 80; i++){
    if((i > 10 && i <= 30) || (i > 50 && i <= 70)){
      motors.setSpeeds(-200, 200);
    }else{
      motors.setSpeeds(200, -200);
    }
    reflectanceSensors.calibrate();
    delay(20);
  }
  motors.setSpeeds(0,0);
  button.waitForButton();
}

void loop(){
  avoidLine();
}

void avoidLine(){
  sensors.read(sensor_values);
  if(sensor_values[0] < QTR_THRESHOLD){
    // if leftmost sensor detects line, turn to the right
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(50);
  }else if(sensor_values[5] < QTR_THRESHOLD){
    // if rightmost sensor detects line, turn to the left
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(50);
  }else{
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}
