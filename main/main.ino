#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <PLabBTSerial.h>
#include <Pushbutton.h>

const int MAX_SPEED = 400;

// DEFINE STATES
int state;
#define SEARCH 0;
#define ATTACK 1;
#define DEFENCE 2;
#define RETURN 3;


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
