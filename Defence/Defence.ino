#include <ZumoMotors.h>
#include <Pushbutton.h>

class Timer{
  long previousMillis, duration;

public:
  Timer(){
    previousMillis = 0;
    duration = 0;
  }

  bool lap(long newDuration){
    if(millis() - previousMillis >= duration){
      previousMillis = millis();
      duration = newDuration;
      return true;
    }
    return false;
  }
};

class Motors{
  ZumoMotors motors;
  Timer motorTimer;
  long previousMillis, driveTime;
  int currentPriority;

public:
  Motors(){
    motors.setSpeeds(0, 0);
    motorTimer.lap(0);
    currentPriority = 0;
  }

  void updateSpeeds(int left, int right, long seconds, int priority){
    if(priority >= currentPriority || motorTimer.lap(seconds)){
      motors.setSpeeds(left, right);
      currentPriority = priority;
    }
  }
};

Pushbutton button(ZUMO_BUTTON);
Motors motors;

bool toRight = true;

void defenseMode(){
  if(toRight){
    motors.updateSpeeds(400,200,1000,1);
  }else{
    motors.updateSpeeds(200,400,1000,1);
  }
}

void evade(int side){
  switch(side){
    case 1: motors.updateSpeeds(-400,-100,500,2); break; //front
    case 2: motors.updateSpeeds(400,100,500,2); break; //back
    case 3: motors.updateSpeeds(400,400,500,2); break; //left
    case 4: motors.updateSpeeds(400,400,500,2); break; //right
    default: break;
  }
}
///////////////////////////////////
void setup(){
  button.waitForButton();
  motors.updateSpeeds(100, 100, 500, 0);
}

void loop(){
  motors.updateSpeeds(400, 200, 500, 1);
  motors.updateSpeeds(0, 0, 500, 0);
}
