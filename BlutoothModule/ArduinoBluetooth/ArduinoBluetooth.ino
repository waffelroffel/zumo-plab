#include <PLabBTSerial.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <NewPing.h>

const int txPin = 7;
const int rxPin = 6;

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

PLabBTSerial btSerial(txPin, rxPin);

void setup() {
  // put your setup code here, to run once:
  btSerial.begin(9600);
  button.waitForButton();

}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  while (i < 10000) {
    btSerial.println(i);
    i = i + 1;
  }

}
