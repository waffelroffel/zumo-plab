//Test av kjoring i ring for å finne target

#define echoPinRight 2 // Right Echo Pin
#define trigPinRight 3 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft 6 // Left Trigger Pin
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <NewPing.h>
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

//Variabler for motor
int lastError = 0;
const int MAX_SPEED = 400;


//Variabler for avstandsmåling
long duration, distance;
int number = 3;
int between = 3;
long maxDistance = 50;
NewPing rightSonar(trigPinRight, trigPinRight, maxDistance);
NewPing leftSonar(trigPinLeft, trigPinLeft, maxDistance);

void setup() {
  button.waitForButton();
  motors.setSpeeds(400,-400);
  searchMode();

}

void loop() {
  searchMode();

}
void searchMode(){
  motors.setSpeeds(400,-400);
  while (getDistance(leftSonar)>maxDistance-10){
    continue;
  }
  motors.setSpeeds(400,400);
  chaseMode(400,400);
  return;
}

void chaseRightMode(int leftSpeed,int rightSpeed){
  if (getDistance(leftSonar)>maxDistance){
    rightSpeed-= 30;
    motors.setSpeeds(leftSpeed, rightSpeed);
  }
  else{
    chaseMode(400,400);
  }
  if (getDistance(rightSonar)>50){
    searchMode();
  }
  return;
}

void chaseLeftMode(int leftSpeed,int rightSpeed){
  if (getDistance(rightSonar)>50){
    leftSpeed -= 30;
    motors.setSpeeds(leftSpeed, rightSpeed);
  }
  else{
    chaseMode(400,400);
  }
  if (getDistance(leftSonar)>50){
    chaseMode(400,400);
  }
  return;
}

void chaseMode(int leftSpeed,int rightSpeed){
  if (getDistance(leftSonar)>50){
    rightSpeed -= 30;
    motors.setSpeeds(leftSpeed,rightSpeed);
    chaseRightMode(leftSpeed,rightSpeed);
  }
  else if  (getDistance(rightSonar)>maxDistance){
    leftSpeed -= 30;
    motors.setSpeeds(leftSpeed,rightSpeed);
    chaseLeftMode(leftSpeed,rightSpeed);
  }
  return;
}

long getDistance(NewPing sonar){
  return sonar.ping_cm();
}
