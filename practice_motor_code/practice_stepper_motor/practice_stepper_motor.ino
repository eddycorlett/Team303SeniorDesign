// decloration of variables 
#include <Stepper.h>

// number will change based on motor used
const int stepsPerRev = 100;

// initialize stepper library on pins
Stepper myStepper(stepsPerRev, 8, 9, 10, 11);

// initialize number of steps the motor has taken
int stepCount = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // read sensor value
  int sensorReading = analogRead(A0);
  // map it to a range from 0 to 100
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  //set motor speed
  if (motorSpeed > 0){
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution 
    myStepper.step(stepsPerRev / 100);
  }

}
