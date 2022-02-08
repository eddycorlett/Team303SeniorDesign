 // variables
const int buttonPin = 12;
const int stepPin = 6;
const int dirPin = 7;
const int enPin = 8;
const int stepsPerRev = 1600; //200000 or a number that doesnt give a warning
const int yDirTime = 2000;    //time it takes for rod to scope out and back in
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
  Serial.println("Hello World");
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
  
 
}

int xDirStepClockwise(){
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

int xDirStepCounterClockwise(){
    //enable motor direction to move counterclockwise
  digitalWrite(dirPin, LOW);
  // makes 200 pulses which equals 1 revolution
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
    }
}

int stopMotor(){
  //stops motor for a certain amount of time or until button is pressed
  for(int x = 0; x < stepsPerRev; x++){
    digitalWrite(enPin, HIGH);
    delayMicroseconds(1000);
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
