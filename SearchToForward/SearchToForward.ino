//Test av kjoring i ring for å finne target

#define echoPinRight 2 // Right Echo Pin
#define trigPinRight 3 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft A0 // Left Trigger Pin
#define maxDistance 50
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <NewPing.h>
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

//Variabler for motor
int lastError = 0;
const int MAX_SPEED = 400;


//Variabler for avstandsmåling
NewPing rightSonar(trigPinRight, echoPinRight, maxDistance);
NewPing leftSonar(trigPinLeft, echoPinLeft, maxDistance);

void setup() {
  Serial.begin(9600);
  button.waitForButton();
  motors.setSpeeds(400,-400);
  searchMode();

}

void loop() {
  Serial.println("Loop started");
  searchMode();

}
void searchMode(){
  Serial.println("Running searchMode");
  motors.setSpeeds(400,-400);
  while ((getDistance(leftSonar)>(maxDistance-10)) or (getDistance(leftSonar)==0)){
    continue;
  }
  motors.setSpeeds(400,400);
  chaseMode(400,400);
  return;
}

void chaseRightMode(int leftSpeed,int rightSpeed){
  Serial.println("Running chaseRightMode");
  if (getDistance(leftSonar)==0){
    rightSpeed-= 30;
    motors.setSpeeds(leftSpeed, rightSpeed);
    chaseRightMode(leftSpeed,rightSpeed);
  }
  else{
    chaseMode(400,400);
  }
  if (getDistance(rightSonar)==0){
    searchMode();
  }
  return;
}

void chaseLeftMode(int leftSpeed,int rightSpeed){
  Serial.println("Running chaseLeftMode");
  if (getDistance(rightSonar)==0){
    leftSpeed -= 30;
    motors.setSpeeds(leftSpeed, rightSpeed);
    chaseLeftMode(leftSpeed,rightSpeed);
  }
  else{
    chaseMode(400,400);
  }
  if (getDistance(leftSonar)==0){
    searchMode();
  }
  return;
}

void chaseMode(int leftSpeed,int rightSpeed){
  Serial.println("Running chaseMode");
  if (getDistance(leftSonar)==0){
    rightSpeed -= 30;
    motors.setSpeeds(leftSpeed,rightSpeed);
    chaseRightMode(leftSpeed,rightSpeed);
  }
  else if  (getDistance(rightSonar)==0){
    leftSpeed -= 30;
    motors.setSpeeds(leftSpeed,rightSpeed);
    chaseLeftMode(leftSpeed,rightSpeed);
  }
  else{
    chaseMode(400,400);
  }
  return;
}

long getDistance(NewPing sonar){
  Serial.println(sonar.ping_cm());
  delay(50);
  return sonar.ping_cm();
}
