//pin definitions
const int enA = 9;
const int in1 = 6;
const int in2 = 7;
const int POT = A0;

//integer to store the motor speed
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

  //write one side high
  digitalWrite(in1, HIGH);
  Serial.begin(9600);
}
void loop() {
  
  //read the value from the potentiometer
  motor_speed = analogRead(POT);
  Serial.println(motor_speed);
  //converts from the 0-1023 input from the potentiometer to 0-255 output for analogWrite
  analogWrite(enA,motor_speed*255.0/1023.0);


}
