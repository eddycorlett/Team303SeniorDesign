// libraries 
const int stepPin = 2;
const int dirPin = 3;
const int enPin = 4;
const int delayValue = 400;
const int stepsPerRev = 3200;

int analogPin1 = 1; // YFINAL analog pin 
int val1 = 0; // Initialize YFINAL
int analogPin = 0; // YSTART analog pin 
int val0 = 1; // Initialize YSTART


void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(analogPin1, INPUT);
  pinMode(analogPin, INPUT);
  digitalWrite(enPin, LOW);
  Serial.begin(9600);
//  Serial.println("Hello World");
}

int moveMotor(){
    //enable motor direction to move clockwise 
  digitalWrite(dirPin, HIGH);
  // makes 200 pulses which equals 1 revolution 
  for (int x = 0; x < stepsPerRev; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayValue);
  }
  

  //delay(1000);
  
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

void loop() {
  //Display YFINAL direction sensor condition
  val1 = analogRead(analogPin1); // read the input pin
  Serial.print(val1); // Write value to serial console
  Serial.println("  YFINAL"); 
  delay(10);
  
  //Display YSTART direction sensor condition
  val1 = analogRead(analogPin); // read the input pin
  Serial.print(val0); // Write value to serial console
  Serial.println("  YSTART"); 
  delay(10);

  if(val1 > 900){
    digitalWrite(enPin, HIGH);
    delay(1000);
  }
  else{
    moveMotor();
  }
}
