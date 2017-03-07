//Test av kjoring i ring for å finne target

#define echoPin 2 // Echo Pin
#define trigPin 3 // Trigger Pin
#include <ZumoMotors.h>
#include <Pushbutton.h>
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

//Variabler for motor
int lastError = 0;
const int MAX_SPEED = 400;


//Variabler for avstandsmåling
long duration, distance;
long distanceToObject;
int maximumRange = 200;
int minimumRange = 0;
int number = 3;
int between = 3;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  button.waitForButton();
  motors.setSpeeds(400,-400);
  searchMode();

}

void loop() {
  delay(2000);
  motors.setSpeeds(0,0);

}
void searchMode(){
  motors.setSpeeds(400,-400);
  while (getDistance(number,between)>20){
    continue;
  }
  motors.setSpeeds(400,400);
  return;
}

long getDistance(int number, int between){
  int i = 0;
  long currentdist = 200;
  while (i < number) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration / 58.2;
    if (distance < currentdist) {
      if (distance >= maximumRange){
        continue;
      }
      else if (distance <= minimumRange){
        continue;
      }
      else{
        currentdist = distance;
      }
    }
    i++;
    delay(between);
  }
  return currentdist;
}

