#include <Servo.h>
Servo SERVO;
//Sending Multiple Variables at Once
//Define LED pins
const int servo_pin = 10;
const int LED_pin = 2;
int current_angle = 90;
//Variables for RGB levels

void setup() {
  pinMode(LED_pin,OUTPUT);
  Serial.begin(9600);  //Serial Port at 9600 baud
  SERVO.attach(servo_pin);
}
void loop() {
  //Keep working as long as data is in the buffer
  while (Serial.available() > 0) {
    current_angle = Serial.parseInt();   //First valid integer
    if (Serial.read() == '\n')  //Done transmitting
    {
      if((current_angle<0)||(current_angle>180)){
        digitalWrite(LED_pin,HIGH);
      } else {
        digitalWrite(LED_pin,LOW);
        SERVO.write(current_angle);
      }
    }
  }
}