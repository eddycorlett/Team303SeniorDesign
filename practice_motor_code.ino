// declocation of variables
int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motorControl1 = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motorControl1, OUTPUT);
}

void loop() {
  // controlling speed
  analogWrite(motorControl1, 1); // ENB pin
  
  digitalWrite(motor1Pin1, HIGH); // on first while LED 
  digitalWrite(motor1Pin2, LOW);  // off first blue LED
  delay(1000);
  
  digitalWrite(motor1Pin1, LOW);  // off first white LED
  digitalWrite(motor1Pin2, HIGH); // on first blue LED
  delay(1000);
}
