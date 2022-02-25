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
const int delayValue = 200;
const int stepsPerRev = 1600; //200000 or a number that doesnt give a warning
//Garmin
const int yDirTime = 2000;    //time it takes for rod to scope out and back in
LIDARLite lidarLite;          //Garmin Variable
int cal_cnt = 0;              //Garmin Variable
int dist;                     //Garmin Distance Variable

//Brush motors
int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;
int buttonPin = 22;

// function declorations
int xDirC;
int xDirCC;
int buttonFunc;
int motorStop;
int revs = 0;
int stopMotorX()

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
int Brushoff(){
  digitalWrite(motor1Pin1, LOW);//left
  digitalWrite(motor2Pin2, LOW);//right
}

int Brushon(){
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

int xDirStepCounterClockwise(){
  digitalWrite(dirPin, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
    }
}
int stopMotorX(){//stops motor for a certain amount of time or until button is pressed
  for(int x = 0; x < stepsPerRev; x++){
    digitalWrite(enPin, HIGH);
    delayMicroseconds(delayValue);
  }
}
void move_motorX(int dist)
{
  if (dist >= 50 ){
        xDirStepCounterClockwise();
      }
  else {
      stopMotorX();
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
  move_motorX(dist);

  // Display distance
  Serial.print(dist);
  Serial.println(" cm");

  delay(10);
}

state_machine(uint8_tsensors)
{
  //Start up Delay
  case zero:
  {
    delayMicroseconds(1000);//delay for system
    //GarminInitial Measurement
    //use sensor to record total distance and name variable dist1 for calculations
  if ( cal_cnt == 0 ) {
    dist1 = lidarLite.distance();      // With bias correction
  } else {
    dist1 = lidarLite.distance(false); // Without bias correction
  }
  
  // Increment reading counter
  cal_cnt++;
  cal_cnt = cal_cnt % 100;
  
  // Display distance
  Serial.print(dist1);
  Serial.println(" cm");
   
  }
  break;
  
  //Initialize all components
  case one:
  {
    //initialize all motors and sensors
    //start brush motors
  }
  break;
  
  //Robot Down in Y-direction
  case two:
  {
    //Turn on y direction motor
  }
  break;

  //Robot Up in Y-direction
  case three:
  {
    //stop y-direction motor and delay
    //Reverse y-direction motor
  }
  break;

  //Move robot in X-direction
  case four:
  {
   //Turn on x direction motor for either set amount or until it has traveled the brush width
   xDirStepCounterClockwise();//motorx on 
  }
  break;

  //Stop the robot 
  case stop:
  {
    stopMotorX();
    //Create function to stopmotorY
  }
  break;
  
}
