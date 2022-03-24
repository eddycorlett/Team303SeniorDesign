<<<<<<< Updated upstream
#include <Wire.h>
#include <LIDARLite.h>
#include <LIDARLite_v3HP.h>
#include <LIDARLite_v4LED.h>


//Global variables/////
//motorX
const int buttonPin = 12;
const int stepPin = 6;
const int dirPin = 7;
const int enPin = 8;
const int delayValue = 200;     //controls the speed of the motor
const int stepsPerRev = 1600;   //controls how long the motor rotates for
//motorY
const int stepPin2 = 2;
const int dirPin2 = 3;
const int enPin2 = 4;
const int delayValue2 = 200;     //controls speed of motor (may need to be adjusted)
const int stepsPerRev2 = 1600;   //controls how long the motor rotates for
//Garmin
const int yDirTime = 2000;    //time it takes for rod to scope out and back in
LIDARLite lidarLite;          //Garmin Variable
int cal_cnt = 0;              //Garmin Variable
int dist;                     //Garmin Distance Variable
//other variables
int state = 0;

//Brush motors (DC motors)
int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;

// function declorations
int xDirC;
int xDirCC;
int buttonFunc;
int motorStop;
int revs = 0;
//int stopMotorX;

void setup() {
  // setting pins as inputs or outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enPin2, OUTPUT);
  pinMode(buttonPin, INPUT);

  //Garmin Sensor Set up
  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations
  Serial.begin(9600);
}

//functions
/*int xDirStepClockwise(){
  //enable motor direction to move clockwise
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  }
*/

//function to turn brush motors off
int Brushoff() {
  digitalWrite(motor1Pin1, LOW);//left
  digitalWrite(motor2Pin2, LOW);//right
}

//function to turn brush motors on
int Brushon() {
  digitalWrite(motor1Pin1, HIGH); //left CW
  digitalWrite(motor2Pin2, HIGH);//right CC
}

/*int Brushturn(){
  delay(1000);
      digitalWrite(motor1Pin1, LOW); //left CC
      digitalWrite(motor2Pin2, LOW);//right CC
  delay(1000); //once we know x distance is met
      digitalWrite(motor1Pin1, HIGH); //left CW
      digitalWrite(motor2Pin2, HIGH);//right CC
  }*/

//function to step motor in the xdirection clockwise
int xDirStepClockwise() {
  //enable motor direction to move clockwise
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
  }
}

//function to step motor in counterclockwise direction
int xDirStepCounterClockwise() {
  digitalWrite(dirPin, LOW);
  digitalWrite(enPin, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
  }
}

//function to stop the motor
int stopMotorX() {
  //stops motor for a certain amount of time or until button is pressed
  for (int x = 0; x < stepsPerRev; x++) {
    digitalWrite(enPin, HIGH);
    delayMicroseconds(delayValue);
  }
}

//funtion to control sensor distance of motorX
void move_motorX(int dist)
{
  if (dist >= 50 ) {
    xDirStepCounterClockwise();
  }
  else {
    stopMotorX();
  }
}

//function to moveY Direction motor down
int move_down_motorY() {
  digitalWrite(dirPin2, LOW); // HIGH and LOW might need to change based on what direction
  digitalWrite(enPin2, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue2);
  }
}

//function to moveY Direction motor up
int move_up_motorY() {
  digitalWrite(dirPin2, HIGH); // HIGH and LOW might need to change based on what direction
  digitalWrite(enPin2, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue2);
  }
}

//function to stop Y directio motor
int stopMotorY() {
  //use Y-direction push button code
}


// main loop
void loop() {
  //Garmin Loop
  // At the beginning of every 100 readings,
  // take a measurement with receiver bias correction
  if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }
  // Increment reading counter
  cal_cnt++;
  cal_cnt = cal_cnt % 100;

  //Call To move motors
  move_motorX(dist);

  // Display distance
  Serial.print(dist);
  Serial.println(" cm");

  delay(10);

  //start of state machie
  switch (state)
  {
     //Start up Delay
   case 0:
    {
      delayMicroseconds(1000);//delay for system
      //GarminInitial Measurement
      //use sensor to record total distance and name variable dist1 for calculations
//    if ( cal_cnt == 0 ) {
//      dist1 = lidarLite.distance();      // With bias correction
//    } else {
//      dist1 = lidarLite.distance(false); // Without bias correction
//    }
//
//     // Increment reading counter
//    cal_cnt++;
//    cal_cnt = cal_cnt % 100;
//
//    // Display distance
//    Serial.print(dist1);
//    Serial.println(" cm");
  }
  break;

  //Initialize all components
  case 1:
    //initialize all motors and sensors
    //start brush motors
    Brushon();
  break;

  //Robot Down in Y-direction
  case 2:
    //Turn on y direction motor
    move_down_motorY();
  break;

  //Robot Up in Y-direction
  case 3:
    //stop y-direction motor and delay
    Brushoff();
    //Reverse y-direction motor
    move_up_motorY();
  break;

  //Move robot in X-direction
  case 4:
   //Turn on x direction motor for either set amount or until it has traveled the brush width
   xDirStepCounterClockwise();//motorx on
  break;

  //Stop the robot
  case 5:
    stopMotorX();
    //Create function to stopmotorY
  break;

  //need an unknown state
  }
}
=======
#include <Wire.h> 
#include <LIDARLite.h> 
#include <LIDARLite_v3HP.h> 
#include <LIDARLite_v4LED.h> 
 
  
 //Global variables 
const int buttonPin = 12; 
const int stepPin = 6; 
const int dirPin = 7; 
const int enPin = 8; 
const int stepsPerRev = 1600; //200000 or a number that doesnt give a warning 
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
 
  //Garmin Sensor Set up 
  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz 
  lidarLite.configure(0); // Change this number to try out alternate configurations 
  Serial.begin(9600); 
} 
 

int xDirStepCounterClockwise(){ 
  digitalWrite(dirPin, LOW); 
  // makes 200 pulses which equals 1 revolution 
  for (int x = 0; x < stepsPerRev; x++){ 
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin, LOW); 
    delayMicroseconds(500); 
    } 
} 
int stopMotor(){//stops motor for a certain amount of time or until button is pressed 
  for(int x = 0; x < stepsPerRev; x++){ 
    digitalWrite(enPin, HIGH); 
    delayMicroseconds(1000); 
  } 
} 
void move_motors(int dist){ 
  if (dist >= 50 ){ 
        xDirStepCounterClockwise(); 
      } 
  else { 
      stopMotor(); 
      } 
  } 
void loop() { 
  //Garmin Loop 
  // At the beginning of every 100 readings, 
  // take a measurement with receiver bias correction 
  if ( cal_cnt == 0 ) { 
    dist = lidarLite.distance();      // With bias correction 
  } else { 
    dist = lidarLite.distance(false); // Without bias correction 
  } 
  // Increment reading counter 
  cal_cnt++; 
  cal_cnt = cal_cnt % 100; 
   
  //Call To move motors 
  move_motors(dist); 
 
  // Display distance 
  Serial.print(dist); 
  Serial.println(" cm"); 
 
  delay(10); 
} 
>>>>>>> Stashed changes
