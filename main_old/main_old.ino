#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <PLabBTSerial.h>
#include <Pushbutton.h>
#include <NewPing.h>
#include <ZumoReflectanceSensorArray.h>
#include <LSM303.h>
#include <QTRSensors.h>
#include <PLab_ZumoMotors.h>
#include <Wire.h>


// DEFINE PINS
#define echoPinRight 4 // Right Echo Pin
#define trigPinRight 5 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft A0 // Left Trigger Pin
#define txPin 7
#define rxPin 6

// DEFINE CONSTANTS
const int MAX_SPEED = 400;
#define maxDistance 50
#define NUM_SENSORS 6
#define QTR_THRESHOLD 1800

// DEFINE STATES
#define SEARCH 0
#define ATTACK 1
#define DEFENCE 2
#define RETURN 3

const int attackSpeed = 300;

// OBJECTS
ZumoMotors motors;
PLab_ZumoMotors plabmotors;
ZumoReflectanceSensorArray sensors;
NewPing rightSonar(trigPinRight, echoPinRight, maxDistance);
NewPing leftSonar(trigPinLeft, echoPinLeft, maxDistance);
LSM303 compass;
PLabBTSerial btSerial(txPin, rxPin);
Pushbutton button(ZUMO_BUTTON);

// Global variables
int state; //States of the vehicle
int previousState;
bool stateSet;
int leftDistance; //Distances to enemies
int rightDistance;
int leftSpeed; // Speeds on the wheels
int rightSpeed;
int previousLeftSpeed;
int previousRightSpeed;
int side; //truffet side
int loopcount; //Antaller loops
unsigned int sensorValues[NUM_SENSORS]; // Array for IR-sensors
boolean crashDetected = false;

// CALIBRATED ACCALERATION
int CALIBRATED_X = 0;
int CALIBRATED_Y = 0;
int CALIBRATED_Z = 0;

void setState(int newState){
  previousState = state;
  state = newState;
}

void getState(){
<<<<<<< HEAD
	// Treffer linja
	if((sensorValues[0] < QTR_THRESHOLD) || (sensorValues[5] < QTR_THRESHOLD)){
		setState(RETURN);
		stateSet = true;
	}
	// Blir kræsjet i
	if (!stateSet && crashDetected) {
		setState(DEFENCE);
		stateSet = true;
	}

	// Kode for å sjekke om vi blir angrepet
	if (!stateSet && (leftDistance > 0 || rightDistance > 0)){
		setState(ATTACK);
		stateSet = true;
	}
	// Alle andre eventuelle sjekker

	if (stateSet == false){ //Dette er siste sjekken, ikke legg noe under
		setState(SEARCH);
		stateSet = true;
	stateSet = false;
	}
=======
  // Treffer linja
  if((sensorValues[1] < QTR_THRESHOLD) || (sensorValues[5] < QTR_THRESHOLD)){
    setState(3);
    stateSet = true;
  }
  // Blir kræsjet i
  if (!stateSet && crashDetected) {
    setState(2);
    stateSet = true;
  }

  // Kode for å sjekke om vi blir angrepet
  if (!stateSet && (leftDistance > 0 || rightDistance > 0)){
    setState(1);
    stateSet = true;
  }
  // Alle andre eventuelle sjekker

  if (stateSet == false){ //Dette er siste sjekken, ikke legg noe under
    setState(0);
    stateSet = true;
  }
  stateSet = false;
  
>>>>>>> d5b3a6310c4d7039b38f61c469a1bf058cfaa90b
}

void evasion() {

  #define FRONT 1
  #define BACK 2
  #define LEFT 3
  #define RIGHT 4

  switch(side){
    case FRONT: updateSpeeds(-400,-100); break; //front
    case BACK: updateSpeeds(400,100); break; //back
    case LEFT: updateSpeeds(400,400); break; //left
    case RIGHT: updateSpeeds(400,400); break; //right
  }
}

void updateSpeeds(int newLeftSpeed, int newRightSpeed){
  previousLeftSpeed = leftSpeed;
  previousRightSpeed = rightSpeed;
  leftSpeed = newLeftSpeed;
  rightSpeed = newRightSpeed;
  motors.setSpeeds(leftSpeed, rightSpeed);
}

int getDistance(NewPing sonar){
  //Serial.println(sonar.ping_cm());
  //return sonar.ping_cm();
  return sonar.convert_cm(sonar.ping_median(4)); //Use multiple reads and get the median (0s are not included)
}

void searchMode(){
  //btSerial.println("Running searchMode");
  updateSpeeds(attackSpeed,-attackSpeed);
}

void retreat(){
  updateSpeeds(0,0);
  plabmotors.backward(attackSpeed,20);
  // if line is detected on both the leftmost and rightmost sensor, start turning around
  if((sensorValues[1] < QTR_THRESHOLD) && (sensorValues[5] < QTR_THRESHOLD)){
     plabmotors.turnRight(attackSpeed, attackSpeed*0.75);
  }else if(sensorValues[1] < QTR_THRESHOLD) {
    // turn right
    plabmotors.turnRight(attackSpeed, 90);
  }else if(sensorValues[5] < QTR_THRESHOLD) {
    // turn left
    plabmotors.turnLeft(attackSpeed, 90);
  }
  plabmotors.forward(attackSpeed, 10);
  return;
}

void attackMode(){
  if (leftDistance>0 && rightDistance>0){
    updateSpeeds(attackSpeed,attackSpeed);
    return;
  }
  if (leftDistance>0){
    if (previousState == 1){
      updateSpeeds(leftSpeed-30, attackSpeed);
    }
    else{
      updateSpeeds(attackSpeed*0.75,attackSpeed);
    }
    return;
  }
  if (rightDistance>0){
    if (previousState == 1){
      updateSpeeds(attackSpeed,rightSpeed - 30);
    }
    else{
      updateSpeeds(attackSpeed,attackSpeed*0.75);
    }
    return;
  }
}
void calibrateAccel() {
    // calibrate accel
    CALIBRATED_X = compass.a.x;
    CALIBRATED_Y = compass.a.y;
    CALIBRATED_Z = compass.a.z;
}

void detectCrash(int x, int y, int z) {
  // I RO:
  // x = -100 (5k dytt) (10k+ 400)
  // y = -130 (5k dytt)
  // z = 17200

  // FREMOVER = POSITIV X
  // BAKOVER = NEGATIV X
  // HOYRE = NEGATIV Y
  // VENSTRE = POSITV Y

  #define FRONT 1
  #define BACK 2
  #define LEFT 3
  #define RIGHT 4

    /* IF MOTORSPEEDS THE SAME THEN
    Check if accel is 0 in y and x direction - if not, then set side and
    crashDetec true
    */
    if (previousLeftSpeed == leftSpeed && previousRightSpeed == rightSpeed) {
        if (state != ATTACK && leftSpeed == rightSpeed) {
            // accel x
            if (x < -250 || x > 0) {
                if (x < 0) {
                    side = FRONT;
                    crashDetected = true;
                    return;
                } else if (x > 0) {
                    side = BACK;
                    crashDetected = true;
                    return;
                }
            }
            // accel y
            else if (y > -250 && y < 0) {
                if (y < 0) {
                    side = RIGHT;
                    crashDetected = true;
                    return;
                } else if (y > 0) {
                    side = LEFT;
                    crashDetected = true;
                    return;
                }
            }
        }
    }
}

void bluetoothPrintArray(int theArray[]) {
  for (int i = 0; i < 6; i++) {
    btSerial.print(theArray[i]);
    btSerial.print('\t');
  }
  btSerial.println();
}
void bluetoothPrint(String message) {
  // ikke brukt ressurser på å sende en tom melding
  if (message.length() > 0) {
    btSerial.println(message);
  }
}

void setup() {
  // SETUP
  Wire.begin();
  sensors.init();
  compass.init();
  btSerial.begin(9600);
  compass.enableDefault();
  //calibrateAccel(); // calibrates accelerometer
  button.waitForButton();
}

void loop() {
  // **ALL** SENSOR INPUT AND CALCULATIONS
  if (loopcount%5==0){
    int first = millis();
    leftDistance = getDistance(leftSonar);
    btSerial.print("Left: ");
    btSerial.println(leftDistance);
    btSerial.print("Right: ");
    btSerial.println(rightDistance);
    rightDistance = getDistance(rightSonar);
    int last = millis();
    btSerial.print("First - last: ");
    btSerial.println(last - first);
    
    
  }
  sensors.read(sensorValues);
  //bluetoothPrintArray(sensorValues);
  detectCrash(compass.a.x, compass.a.y, compass.a.z);
  loopcount++; //Add one to number of loops
  // DECIDE STATE BASED ON SENSOR INPUT
  getState();

  // SWITCH-CASE
  switch (state) {
    case SEARCH:
      //bluetoothPrint("searchMode\n");
      searchMode();
      break;
    case ATTACK:
     // bluetoothPrint("attackMode\n");
      attackMode();
      break;
    case DEFENCE:
      //bluetoothPrint("Defence\n");
      evasion();
      break;
    case RETURN:
      //bluetoothPrint("Retreat\n");
      retreat();
      break;
  }
}
