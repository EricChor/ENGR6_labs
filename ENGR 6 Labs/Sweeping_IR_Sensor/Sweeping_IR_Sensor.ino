/* Sweeping Distance Sensor
The program employs a simple function that rotates the servo to the
requested degree, takes the distance measurement, scales it, and
then turns on an LED with a brightness proportional to the
distance. */
#include <Servo.h>
const int SERVO =9; //Servo on Pin 9
const int IR =A0; //IR Distance Sensor on Analog Pin 0
const int LED1 =3; //LED Output 1
const int LED2 =5; //LED Output 2
const int LED3 =6; //LED Output 3
const int LED4 =11; //LED Output 4
Servo myServo; //Servo Object
int dist1 = 0; //Quadrant 1 Distance
int dist2 = 0; //Quadrant 2 Distance
int dist3 = 0; //Quadrant 3 Distance
int dist4 = 0; //Quadrant 4 Distance
void setup()
{
  myServo.attach(SERVO);
  Serial.begin(9600);
}
void loop()
{
  dist1 = readDistance(15);
  dist1 = map(dist1,4,40,0,1023);
  analogWrite(LED1,dist1);
  dist2 = readDistance(65);
  dist2 = map(dist1,4,40,0,1023);
  analogWrite(LED2,dist2);
  dist3 = readDistance(115);
  dist3 = map(dist1,4,40,0,1023);
  analogWrite(LED3,dist3);
  dist4 = readDistance(165);
  dist4 = map(dist1,4,40,0,1023);
  analogWrite(LED4,dist4);
  delay(10000000);
}
int readDistance(int pos)
{
  myServo.write(pos);
  delay(1000);
  float distance = analogRead(IR);
  distance = distance * 5000 / 1024;
  distance = constrain(distance,0,3000);
  distance = map(distance,3000,0,4.0,40.0);
  Serial.println(distance);
  return distance;
}