/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low accelerometer and
magnetometer data registers. They can be converted to units of g and
gauss using the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM303D gives a magnetometer X axis reading of 1982 with
its default full scale setting of +/- 4 gauss. The M_GN specification
in the LSM303D datasheet (page 10) states a conversion factor of 0.160
mgauss/LSB (least significant bit) at this FS setting, so the raw
reading of -1982 corresponds to 1982 * 0.160 = 317.1 mgauss =
0.3171 gauss.

In the LSM303DLHC, LSM303DLM, and LSM303DLH, the acceleration data
registers actually contain a left-aligned 12-bit number, so the lowest
4 bits are always 0, and the values should be shifted right by 4 bits
(divided by 16) to be consistent with the conversion factors specified
in the datasheets.

Example: An LSM303DLH gives an accelerometer Z axis reading of -16144
with its default full scale setting of +/- 2 g. Dropping the lowest 4
bits gives a 12-bit raw value of -1009. The LA_So specification in the
LSM303DLH datasheet (page 11) states a conversion factor of 1 mg/digit
at this FS setting, so the value of -1009 corresponds to -1009 * 1 =
1009 mg = 1.009 g.
*/

#include <Wire.h>
#include <LSM303.h>
#include <PLabBTSerial.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

const int txPin = 7;
const int rxPin = 6;

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

PLabBTSerial btSerial(txPin, rxPin);

LSM303 compass;

char report[80];

// CALIBRATED ACCALERATION
int CALIBRATED_X = 0;
int CALIBRATED_Y = 0;
int CALIBRATED_Z = 0;

int left_motor;
int right_motor;

void setup()
{
    //btSerial.begin(9600);
    btSerial.begin(9600);
    button.waitForButton();
    Wire.begin();
    compass.init();
    compass.enableDefault();
    //calibrateAccel();
}

void loop()
{
  compass.read();

  motors.setSpeeds(400, 400);
  snprintf(report, sizeof(report), "A: %6d %6d %6d    M: %6d %6d %6d",
    compass.a.x, compass.a.y, compass.a.z,
    compass.m.x, compass.m.y, compass.m.z);

  //btSerial.println(report);
  btSerial.println(report);
  //detectCrash(compass.a.x, compass.a.y, compass.a.z);

  delay(100);
}

void calibrateAccel() {
    // calibrate accel
    CALIBRATED_X = compass.a.x;
    CALIBRATED_Y = compass.a.y;
    CALIBRATED_Z = compass.a.z;
}

void crashDetected(int x, int y, int z) {
// I RO:
// x = -100 (5k dytt) (10k+ 400)
// y = -130 (5k dytt)
// z = 17200

// FREMOVER = POSITIV X
// BAKOVER = NEGATIV X
// HOYRE = NEGATIV Y
// VENSTRE = POSITV Y

    boolean crash_x = false;
    boolean crash_y = false;


    /* if (state = ATTACK) {
        if (previousLeftSpeed == leftSpeed && previousRightSpeed == rightSpeed){
            if ()
        }
    } */

    // 0 accel x
    if (x > -250 && x < 0) {
        crash_x = false;
    }
    // 0 accel y
    else if (y > -250 && y < 0) {
        crash_y = false;
    }

}
