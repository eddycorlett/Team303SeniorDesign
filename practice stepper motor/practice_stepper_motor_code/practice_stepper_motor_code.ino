<<<<<<< Updated upstream
//files included 
#include <Wire.h>
#include <LIDARLite.h>
#include <LIDARLite_v3HP.h>
#include <LIDARLite_v4LED.h>

// variables
const int buttonPin = 12;
const int stepPin = 6;
const int dirPin = 7;
const int enPin = 8;
const int delayValue = 200;   //controls the speed of the motor
const int stepsPerRev = 1600; //controls how long the motor rotates for
const int yDirTime = 2000;    //time it takes for rod to scope out and back in
LIDARLite lidarLite;          //Garmin Variable
int cal_cnt = 0;              //Garmin Variable
int dist;                     //Garmin Distance Variable

// function declorations
int xDirC;
int xDirCC;
int buttonFunc;
int motorStop;
int revs = 0;
int buttonState = 0; //represents if sensor goes LOW

void setup() {
  // setting pins as inputs or outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  //Serial.println("Hello World");

  //Garmin sensor set up
//  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
//  lidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop() {
  //for loop to start motor based on time
  for(revs = 0; revs < 5; revs++){
      digitalWrite(enPin, LOW);
      xDirC = xDirStepClockwise();
      Serial.print(revs);
  }
  //for loop to stop motor based on time
  for(revs = 0; revs < 5; revs++){
      digitalWrite(enPin, HIGH);
      motorStop = stopMotor();
      Serial.print("stopped");
  }
  //buttonFunc = pressButton();
  //xDirCC = xDirStepCounterClockwise();
  
//   //Garmin Loop
//  // At the beginning of every 100 readings,
//  // take a measurement with receiver bias correction
//  if ( cal_cnt == 0 ) {
//    dist = lidarLite.distance();      // With bias correction
//  } else {
//    dist = lidarLite.distance(false); // Without bias correction
//  }
//  // Increment reading counter
//  cal_cnt++;
//  cal_cnt = cal_cnt % 100;
//  
//  //Call To move motors
//  move_motors(dist);
//
//  // Display distance
//  Serial.print(dist);
//  Serial.println(" cm");
//
//  delay(10);
}

int xDirStepClockwise(){
  //enable motor direction to move clockwise 
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses which equals 1 revolution 
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
  }
}

int xDirStepCounterClockwise(){
    //enable motor direction to move counterclockwise
  digitalWrite(dirPin, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
    }
}

int stopMotor(){
  //stops motor for a certain amount of time or until button is pressed
  for(int x = 0; x < stepsPerRev; x++){
    digitalWrite(enPin, HIGH);
    delayMicroseconds(delayValue);
  }
  // alternate //  
  //if (buttonState == LOW){
  //  for(x = 0; x < yDirTime; x++){
  //
//    digitalWrite(enPin, HIGH);
  //}
//  }
//  else{
//    digitalWrite(enPin, LOW);
//  }

  //alternate forloop for button pressed
  //maybe use different expression, better solution
//  for(int x = 0; x == buttonState; x++){
//    
//  }
}

void move_motors(int dist){
  if (dist >= 50 ){
        xDirStepCounterClockwise();
      }
  else {
      stopMotor();
      }
  }

int pressButton(){
  buttonState = digitalRead(buttonPin);

  // HIGH = pressed
  if (buttonState == HIGH){
    //turn off stepper motor
    digitalWrite(enPin, HIGH);
    Serial.print("Button has been pressed");
    Serial.print(buttonState);
  }
  else {
    //continue motor oporation as normal 
    digitalWrite(enPin, LOW);
    Serial.print("Button NOT pressed");
    Serial.print(buttonState);
  }
  //resetting button state
  buttonState = 0;
}
=======
//files included 
#include <Wire.h>
#include <LIDARLite.h>
#include <LIDARLite_v3HP.h>
#include <LIDARLite_v4LED.h>

// variables
const int buttonPin = 12;
const int stepPin = 6;
const int dirPin = 7;
const int enPin = 8;
const int delayValue = 200;   //controls the speed of the motor
const int stepsPerRev = 1600; //controls how long the motor rotates for
const int yDirTime = 2000;    //time it takes for rod to scope out and back in
LIDARLite lidarLite;          //Garmin Variable
int cal_cnt = 0;              //Garmin Variable
int dist;                     //Garmin Distance Variable

// function declorations
int xDirC;
int xDirCC;
int buttonFunc;
int motorStop;
int revs = 0;
int buttonState = 0; //represents if sensor goes LOW

void setup() {
  // setting pins as inputs or outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  //Serial.println("Hello World");

  //Garmin sensor set up
  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop() {
  //for loop to start motor based on time
  for(revs = 0; revs < 5; revs++){
      digitalWrite(enPin, LOW);
      xDirC = xDirStepClockwise();
      Serial.print(revs);
  }
  //for loop to stop motor based on time
  for(revs = 0; revs < 5; revs++){
      digitalWrite(enPin, HIGH);
      motorStop = stopMotor();
      Serial.print("stopped");
  }
  //buttonFunc = pressButton();
  //xDirCC = xDirStepCounterClockwise();
  
//   //Garmin Loop
//  // At the beginning of every 100 readings,
//  // take a measurement with receiver bias correction
//  if ( cal_cnt == 0 ) {
//    dist = lidarLite.distance();      // With bias correction
//  } else {
//    dist = lidarLite.distance(false); // Without bias correction
//  }
//  // Increment reading counter
//  cal_cnt++;
//  cal_cnt = cal_cnt % 100;
//  
//  //Call To move motors
//  move_motors(dist);
//
//  // Display distance
//  Serial.print(dist);
//  Serial.println(" cm");
//
//  delay(10);
}

int xDirStepClockwise(){
  //enable motor direction to move clockwise 
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses which equals 1 revolution 
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
  }
}

int xDirStepCounterClockwise(){
    //enable motor direction to move counterclockwise
  digitalWrite(dirPin, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
    }
}

int stopMotor(){
  //stops motor for a certain amount of time or until button is pressed
  for(int x = 0; x < stepsPerRev; x++){
    digitalWrite(enPin, HIGH);
    delayMicroseconds(delayValue);
  }
  // alternate //  
  //if (buttonState == LOW){
  //  for(x = 0; x < yDirTime; x++){
  //
//    digitalWrite(enPin, HIGH);
  //}
//  }
//  else{
//    digitalWrite(enPin, LOW);
//  }

  //alternate forloop for button pressed
  //maybe use different expression, better solution
//  for(int x = 0; x == buttonState; x++){
//    
//  }
}

void move_motors(int dist){
  if (dist >= 50 ){
        xDirStepCounterClockwise();
      }
  else {
      stopMotor();
      }
  }

//int pressButton(){
//  buttonState = digitalRead(buttonPin);
//
//  // HIGH = pressed
//  if (buttonState == HIGH){
//    //turn off stepper motor
//    digitalWrite(enPin, HIGH);
//    Serial.print("Button has been pressed");
//    Serial.print(buttonState);
//  }
//  else {
//    //continue motor oporation as normal 
//    digitalWrite(enPin, LOW);
//    Serial.print("Button NOT pressed");
//    Serial.print(buttonState);
//  }
//  //resetting button state
//  buttonState = 0;
//}
>>>>>>> Stashed changes
