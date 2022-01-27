// libraries 

//what are you doing stepPin

const int stepPinY = 5;
const int stepPinX = 6;
const int dirPin = 7;
const int enPin = 8;
const int xSensor = 9;
const int ySensor = 10;

int xValue;
int yValue;
int x = 0;

void setup() {
  pinMode(stepPinY, OUTPUT);
  pinMode(stepPinX, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(xSensor, INPUT);
  pinMode(ySensor, INPUT);
  
  
  digitalWrite(enPin, LOW);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  //enable motor direction to move
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses


  /* 
   X direction will be based on Y direction movement
   We need to activate the "xMove" function when the Y direction has completed its function
   */

  /*
   digitalRead function returns either high or low. This represents
   the X sensor deciding whether or not the bot moves
   */

//start code here! assume position is LEFT side of array and rod is RETRACTED

  

  //start by reading sensors
  xValue = digitalRead(xSensor);
  yValue = digitalRead(ySensor);

  
    xMove();

  

  //extend rod

  if(yValue == HIGH){
    extendRod();
    delay(1000);  
  }else{
  retractRod();
  xStepRight();
  delay(1000);
  }
  
 /*
  
  
  //enable motor direction to move
  digitalWrite(dirPin, LOW);
  // makes 200 pulses
  for (int x = 0; x < 2000000; x++){
    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinX, LOW);
    delayMicroseconds(500);
  }
  Serial.println("Second FOR loop");
  */
}

void xStepRight(){

    for (int x = 0; x < 2000; x++){
      //stepPinX, HIGH to turn motor clockwise
      digitalWrite(stepPinX, HIGH);
      delayMicroseconds(500);
    }
  
}
void xStepLeft(){

    for (int x = 0; x < 2000; x++){
      //stepPinX, HIGH to turn motor clockwise
      digitalWrite(stepPinX, LOW);
      delayMicroseconds(500);
    }
  
}

void extendRod(){

  for (int x = 0; x < 2000; x++){
      //stepPinY, HIGH to turn motor clockwise
      digitalWrite(stepPinY, HIGH);
      delayMicroseconds(500);
    }

}
void retractRod(){

  for (int x = 0; x < 2000; x++){
      //stepPinY, HIGH to turn motor clockwise
      digitalWrite(stepPinY, LOW);
      delayMicroseconds(500);
    }

}
