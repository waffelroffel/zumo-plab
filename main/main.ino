#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <PLabBTSerial.h>
#include <Pushbutton.h>
#include <NewPing.h>

// DEFINE PINS
#define echoPinRight 2 // Right Echo Pin
#define trigPinRight 3 // Right Trigger Pin
#define echoPinLeft A1 // Left Echo Pin
#define trigPinLeft A0 // Left Trigger Pin


// DEFINE CONSTANTS
const int MAX_SPEED = 400;
#define maxDistance 50

// DEFINE STATES
int state;
#define SEARCH 0;
#define ATTACK 1;
#define DEFENCE 2;
#define RETURN 3;

// Variables for distance measurements
NewPing rightSonar(trigPinRight, echoPinRight, maxDistance);
NewPing leftSonar(trigPinLeft, echoPinLeft, maxDistance);


void setup() {
    // SETUP AND MANOUVER TO MIDDLE
    sensors.init();
    motors.setSpeeds(400,120);
    delay(750);
    motors.setSpeeds(0,0);
}

void loop() {

    // **ALL** SENSOR INPUT AND CALCULATIONS

    // DECIDE STATE BASED ON SENSOR INPUT

    // SWITCH-CASE
    switch (state) {
        case SEARCH:
            // SEARCH LOGIC
            break;
        case ATTACK:
            // ATTACK LOGIC
            break;
        case DEFENCE:
            // DEFENCE LOGIC
            break;
        case RETURN:
            // RETURN LOGIC
            break;
        }
    }

}

long getDistance(NewPing sonar){
  Serial.println(sonar.ping_cm());
  delay(50);
  return sonar.ping_cm();
}
