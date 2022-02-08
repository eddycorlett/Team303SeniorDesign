// libraries 
const int stepPin = 6;
const int dirPin = 7;
const int enPin = 8;
const int stepsPerRev = 200000;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
//  Serial.begin(9600);
//  Serial.println("Hello World");
}

void loop() {
  //enable motor direction to move clockwise 
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses which equals 1 revolution 
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  

  //delay(1000);
  
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
