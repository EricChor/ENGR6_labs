//Simple Motor Speed Control Program
const int MOTOR = 9;  //Motor on Digital Pin 9
const int POT = A0;
int Pot_input = 0;
void setup() {
  pinMode(MOTOR, OUTPUT);
  pinMode(POT, INPUT);
  Serial.begin(9600);
}
void loop() {
  // ramp up the speed, delay 10 ms after write for motor to react
  Pot_input = analogRead(POT);
  Serial.println(Pot_input);
  analogWrite(MOTOR,Pot_input);
  delay(10);

  // ramp down the speed, delay 10 ms after write for motor to react
}