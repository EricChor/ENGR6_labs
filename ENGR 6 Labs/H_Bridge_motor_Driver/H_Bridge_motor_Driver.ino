/* Code for Lab 15: Moving the motor forward and reverse,
and also ramping the speed up and down.*/
const int enA = 9;
const int in1 = 6;
const int in2 = 7;
const int POT = A0;

int motor_speed = 0;


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(POT, INPUT);

  // ensure motors stopped
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(100);

  digitalWrite(in1, HIGH);
  Serial.begin(9600);
}
void loop() {
  
  motor_speed = analogRead(POT);
  Serial.println(motor_speed);
  analogWrite(enA,motor_speed*255.0/1023.0);


}
