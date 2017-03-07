//Test av kjoring i ring for å finne target

#define echoPinRight 2 // Right Echo Pin
#define trigPinRight 3 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft 6 // Left Trigger Pin
#include <ZumoMotors.h>
#include <Pushbutton.h>
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

//Variabler for motor
int lastError = 0;
const int MAX_SPEED = 400;


//Variabler for avstandsmåling
long duration, distance;
int number = 3;
int between = 3;

void setup() {
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  button.waitForButton();
  motors.setSpeeds(400,-400);
  searchMode();

}

void loop() {
  chaseMode(400,400);

}
void searchMode(){
  motors.setSpeeds(400,-400);
  while (getDistance(trigPinLeft, echoPinLeft)>40){
    continue;
  }
  motors.setSpeeds(400,400);
  chaseMode(400,400);
  return;
}

void chaseRightMode(int leftSpeed,int rightSpeed){
  if (getDistance(trigPinLeft, echoPinLeft)>50){
    rightSpeed-= 30;
    motors.setSpeeds(leftSpeed, rightSpeed);
  }
  else{
    chaseMode(400,400);
  }
  if (getDistance(trigPinRight, echoPinRight)>50){
    searchMode();
  }
  return;
}

void chaseLeftMode(int leftSpeed,int rightSpeed){
  if (getDistance(trigPinLeft, echoPinLeft)>50){
    leftSpeed -= 30;
    motors.setSpeeds(leftSpeed, rightSpeed);
  }
  else{
    chaseMode(400,400);
  }
  if (getDistance(trigPinLeft, echoPinLeft)>50){
    chaseMode(400,400);
  }
  return;
}

void chaseMode(int leftSpeed,int rightSpeed){
  if (getDistance(trigPinLeft, echoPinLeft)>50){
    rightSpeed -= 30;
    motors.setSpeeds(leftSpeed,rightSpeed);
    chaseRightMode(leftSpeed,rightSpeed);
  }
  else if  (getDistance(trigPinRight, echoPinRight)>50){
    leftSpeed -= 30;
    motors.setSpeeds(leftSpeed,rightSpeed);
    chaseLeftMode(leftSpeed,rightSpeed);
  }
  return;
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
