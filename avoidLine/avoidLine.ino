#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <PLab_ZumoMotors.h>

#define QTR_THRESHOLD  500

#define TURN_SPEED  400
#define FORWARD_SPEED 400
 
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

PLab_ZumoMotors plab_Motors;

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;

void setup(){
  sensors.init();
  motors.setSpeeds(400,400);
}

void loop(){
  avoidLine();
}

void avoidLine(){
  sensors.read(sensor_values);
  if(sensor_values[0] < QTR_THRESHOLD){
    motors.setSpeeds(FORWARD_SPEED, 300);
    delay(100);
  }else if(sensor_values[5] < QTR_THRESHOLD){
    motors.setSpeeds(300, FORWARD_SPEED);
    delay(100);
  }else{
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
}
