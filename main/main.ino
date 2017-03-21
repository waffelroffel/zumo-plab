#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <PLabBTSerial.h>
#include <Pushbutton.h>
#include <NewPing.h>
#include <ZumoReflectanceSensorArray.h>
#include <LSM303.h>

// DEFINE PINS
#define echoPinRight 2 // Right Echo Pin
#define trigPinRight 3 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft A0 // Left Trigger Pin

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

// OBJECTS
ZumoMotors motors;
ZumoReflectanceSensorArray sensors;
NewPing rightSonar(trigPinRight, echoPinRight, maxDistance);
NewPing leftSonar(trigPinLeft, echoPinLeft, maxDistance);

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
unsigned int sensorValues[NUM_SENSORS]; // Array for IR-sensors

// CALIBRATED ACCALERATION
int CALIBRATED_X = 0;
int CALIBRATED_Y = 0;
int CALIBRATED_Z = 0;

void setState(int newState){
	previousState = state;
	state = newState;
}

void getState(){
	// Treffer linja
	if((sensorValues[0] < QTR_THRESHOLD) || (sensorValues[5] < QTR_THRESHOLD)){
		setState(RETURN);
		stateSet = true;
	}
	// Blir kræsjet i
	if (!statSet && crashDetected) {
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
}

void evasion(){
	switch(side){
		case 1: updateSpeeds(-400,-100); break; //front
		case 2: updateSpeeds(400,100); break; //back
		case 3: updateSpeeds(400,400); break; //left
		case 4: updateSpeeds(400,400); break; //right
	}
}

void updateSpeeds(int newLeftSpeed, int newRightSpeed){
	previousLeftSpeed = leftSpeed;
	previousRightSpeed = rightSpeed;
	leftSpeed = newLeftSpeed;
	rightSpeed = newRightSpeed;
	motors.setSpeeds(leftSpeed, rightSpeed);
}

long getDistance(NewPing sonar){
	//Serial.println(sonar.ping_cm());
	return sonar.ping_cm();
}

void searchMode(){
	//btSerial.println("Running searchMode");
	updateSpeeds(400,-400);
}

void retreat(){
	// if line is detected on both the leftmost and rightmost sensor, start turning around
	if((sensorValues[0] < QTR_THRESHOLD) && (sensorValues[5] < QTR_THRESHOLD)){
		updateSpeeds(-300, 300);
	}else if(sensorValues[0] < QTR_THRESHOLD){
		// turn right
		updateSpeeds(300, 200);
	}else if(sensorValues[5] < QTR_THRESHOLD) {
		// turn left
		updateSpeeds(200, 300);
	}
}

void attackMode(){
	if (leftDistance>0 && rightDistance>0){
		updateSpeeds(400,400);
		return;
	}
	if (leftDistance>0){
		if (previousState == 1){
			updateSpeeds(leftSpeed-30, 400);
		}
		else{
			updateSpeeds(370,400);
		}
		return;
	}
	if (rightDistance>0){
		if (previousState == 1){
			updateSpeeds(400,rightSpeed);
		}
		else{
			updateSpeeds(400,370);
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

    /* IF MOTORSPEEDS THE SAME THEN
    Check if accel is 0 in y and x direction - if not, then set side and
    crashDetec true
    */
    if (previousLeftSpeed == leftSpeed && previousRightSpeed == rightSpeed) {
        if (state != ATTACK && leftSpeed == rightSpeed) {
            // accel x
            if (x < -250 || x > 0) {
                if (x < 0) {
                    side = 1;
                    crashDetected = true;
                    return;
                } else if (x > 0) {
                    side = 2;
                    crashDetected = true;
                    return;
                }
            }
            // accel y
            else if (y > -250 && y < 0) {
                if (y < 0) {
                    side = 4;
                    crashDetected = true;
                    return;
                } else if (y > 0) {
                    side = 3;
                    crashDetected = true;
                    return;
                }
            }
        }
    }
}

void setup() {
	// SETUP
	sensors.init();
	compass.init();
	compass.enableDefault();
	calibrateAccel(); // calibrates accelerometer
}

void loop() {
	// **ALL** SENSOR INPUT AND CALCULATIONS
	leftDistance = getDistance(leftSonar);
	rightDistance = getDistance(rightSonar);
	sensors.read(sensorValues);
	detectCrash(compass.a.x, compass.a.y, compass.a.z);

	// DECIDE STATE BASED ON SENSOR INPUT
	getState();

	// SWITCH-CASE
	switch (state) {
		case SEARCH: searchMode(); break;
		case ATTACK: attackMode(); break;
		case DEFENCE: evasion(); break;
		case RETURN: retreat(); break;
	}
}
