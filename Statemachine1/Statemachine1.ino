#include <Wire.h> 
#include <LIDARLite.h> 
#include <LIDARLite_v3HP.h> 
#include <LIDARLite_v4LED.h> 
 
void state_machine_run();
void YUp();
void YDown();
void XmotorMove();
void stopMotorX();
void stopMotorY();

enum State_enum {MoveYDown, Delay1, MoveYUp, Check, XMove, STOP};
//enum Sensors_enum {NONE, val1, val0, dist};
//uint8_t read_IR();
uint8_t state = MoveYDown;  

 //Xmotor Values
const int stepPin = 6; 
const int dirPin = 7; 
const int enPin = 8; 
const int delayValue = 200;
const int stepsPerRev = 1600; //200000 or a number that doesnt give a warning 
const int yDirTime = 2000;    //time it takes for rod to scope out and back in 

//Ymotor Values
const int stepPin2 = 2;
const int dirPin2 = 3;
const int enPin2 = 4;
const int delayValue2 = 400;
const int stepsPerRev2 = 3200;

//Garmin Values
LIDARLite lidarLite;          //Garmin Variable 
int cal_cnt = 0;              //Garmin Variable 
int dist;                     //Garmin Distance Variable 
 
// function declorations 
int xDirC; 
int xDirCC; 
int buttonFunc; 
int motorStop; 
int revs = 0; 
int brushwidth = 60.96; 

//Y direction sensor pins
int analogPin1 = 1; // YFINAL analog pin 
int val1 = 0; // Initialize YFINAL
int analogPin = 0; // YSTART analog pin 
int val0 = 0; // Initialize YSTART
 
void setup() { 
  // Xmotor pins as inputs or outputs 
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT); 
  pinMode(enPin, OUTPUT);  

 // Ymotor pins as inputs or outputs 
  pinMode(stepPin2, OUTPUT); 
  pinMode(dirPin2, OUTPUT); 
  pinMode(enPin2, OUTPUT);  
  
  //Garmin Sensor Set up 
  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz 
  lidarLite.configure(0); // Change this number to try out alternate configurations 
  Serial.begin(9600);
} 

void loop(){
  //Start State Machine loop  
  state_machine_run();
  delay(10);
  
  //Garmin Loop  
  if ( cal_cnt == 0 ) { 
    dist = lidarLite.distance();      // With bias correction 
  } else { 
    dist = lidarLite.distance(false); // Without bias correction 
  } 
  // Increment reading counter 
  cal_cnt++; 
  cal_cnt = cal_cnt % 100; 
 
// Display distance 
  Serial.print(dist); 
  Serial.println(" cm"); 
    delay(10); 

//Display YFINAL direction sensor condition
 val1 = analogRead(analogPin1); // read the input pin
Serial.print(val1); // Write value to serial console
Serial.println("  YFINAL"); 
  delay(10);
  
//Display YSTART direction sensor condition
 val0 = analogRead(analogPin); // read the input pin
Serial.print(val0); // Write value to serial console
Serial.println("  YSTART"); 
  delay(10);
  

}

void state_machine_run() 
{
  switch(state)
  {
    case MoveYDown:
      if((val1=0)&& (val0=0)){            //If both sensors are pressed
        YDown();                     //Move Down in Y-Direction
        Serial.print(MoveYDown);
        state = Delay1;
      }
      break;

      case Delay1:                        //Delay YMotor
      if((val1 >= 1)&& (val0= 1)){
        stopMotorY();                     //Stop Motor Y to reverse polarity
        state = MoveYUp;
        Serial.print(Delay1);
      }
      break;

      case MoveYUp:                             //Move Y motor Upwards
      if((val1 >= 1)&& (val0= 1)){
        YUp();                                  //Stop Motor Y to reverse polarity
        state = Check;
      }
      break;
      
      case Check:                                //Check conditions before Xmove
      if((val1 = 0)&& (val0= 0) && (dist >= brushwidth))
      {
        state = XMove; 
      }
      else{
        state = STOP;
      }
      break;

      case XMove:
      if((val1 = 0)&& (val0= 0) && (dist >= brushwidth))
      {
        stopMotorY();
        XmotorMove();
        state = YDown; 
      }
      else{
        state = STOP;
      }
      break;

    case STOP:
//      if(val0 == NONE) && {              //Sensors Not reading
//       stopMotorX();
//       stopMotorY();
//       state = STOP;                     //Feed back loop
//      }
//      
      if(dist >= brushwidth){   //Re-Check of measurment
        state = YDown;                   // False Reading Proceed to YDown state
      }
      else{                              // Distance to short Feed back loop
        state = STOP;
      }
      break;
  }
}
 
void YUp(){
    //enable motor direction to move clockwise 
  digitalWrite(dirPin2, HIGH);
  digitalWrite(enPin2, LOW);
  // makes 200 pulses which equals 1 revolution 
  for (int x = 0; x < stepsPerRev2; x++){
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(delayValue2);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(delayValue2);
  }
}
 
void YDown(){
//enable motor direction to move counterclockwise
  digitalWrite(dirPin2, LOW);
  digitalWrite(enPin2, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev2; x++){
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(delayValue2);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(delayValue2);
  }
}
void XmotorMove(){ 
  digitalWrite(dirPin, LOW); 
  digitalWrite(enPin, LOW); 
  // makes 200 pulses which equals 1 revolution 
  for (int x = 0; x < stepsPerRev; x++){ 
    digitalWrite(stepPin, HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin, LOW); 
    delayMicroseconds(500); 
    } 
} 
void stopMotorX(){                                //stops motor for a certain amount of time or until button is pressed 
  for(int x = 0; x < stepsPerRev; x++){ 
    digitalWrite(enPin, HIGH); 
    delayMicroseconds(500); 
  } 
}
void stopMotorY(){                                //stops motor for a certain amount of time or until button is pressed 
  for(int x = 0; x < stepsPerRev2; x++){ 
    digitalWrite(enPin2, HIGH); 
    delayMicroseconds(500); 
  } 
} 
 
//uint8_t read_IR()                      //code for reading sensors
//{
  
//} 


 
