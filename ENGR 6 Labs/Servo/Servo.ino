//Servo Potentiometer Control
#include <Servo.h>
const int SERVO=6; //Servo on Pin 9
const int POT=A0; //POT on Analog Pin 0
Servo myServo;
int val = 0; //for storing the reading from the POT
void setup()
{
myServo.attach(SERVO);
Serial.begin(9600);
}
void loop()
{
val = analogRead(POT); //Read Pot
val = map(val, 0, 1023, 0, 179); //scale it to servo range
Serial.println(val);
myServo.write(val); //sets the servo
delay(15); //waits for the servo
}