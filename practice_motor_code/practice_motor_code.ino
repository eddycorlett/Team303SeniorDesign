// declocation of variables
int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;
int buttonPin = 22;
int buttonState = 0;
//int x = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
//  for(int x=0; x <=100; x++){
//    
//  }
  if (buttonPin == HIGH){
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor2Pin1, LOW);
  }
  else{
      digitalWrite(motor1Pin1, HIGH); // on first while LED 
      digitalWrite(motor2Pin1, HIGH);
      delay(1000);
  }

}
