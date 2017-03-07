#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <PLabBTSerial.h>
#include <Pushbutton.h>

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

const int MAX_SPEED = 400;

int state;
// tilstander: 
// 0 = før start
// 1 = søk
// 2 = angrep
// 3 = forsvar



void setup() {
  state = 0;
  button.waitForButton();
  
  
  
}

void loop() {

}
