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

}


void bluetoothPrint(String message) {
  // ikke brukt ressurser på å sende en tom melding
  if (message.length() > 0) {
    btSerial.print(message);
  }
}

