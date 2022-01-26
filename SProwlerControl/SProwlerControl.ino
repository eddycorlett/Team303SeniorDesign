// libraries 
const int stepPin = 6;
const int dirPin = 7;
const int enPin = 8;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  //enable motor direction to move
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses
  for (int x = 0; x < 2000000; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  Serial.println("First FOR loop");

  delay(1000);
  
  //enable motor direction to move
  digitalWrite(dirPin, LOW);
  // makes 200 pulses
  for (int x = 0; x < 2000000; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  Serial.println("Second FOR loop");
  
}
