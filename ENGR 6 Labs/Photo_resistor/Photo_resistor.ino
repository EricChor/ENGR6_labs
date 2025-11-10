//Automatic Nightlight
const int RLED=9; //Red LED on pin 9 (PWM)
const int LIGHT=A0; //Lght Sensor on analog pin 0
const int MIN_LIGHT=50; //Minimum expected light value
const int MAX_LIGHT=240; //Maximum Expected Light value
int val = 0; //variable to hold the analog reading
void setup()
{
  pinMode(RLED, OUTPUT); //Set LED pin as output
  pinMode(LIGHT, INPUT);
  Serial.begin(9600);
}
void loop()
{
  val = analogRead(LIGHT); //Read the light sensor
  Serial.println(val);
  val = map(val, MIN_LIGHT, MAX_LIGHT, 255, 0);//Map the light reading
  val = constrain(val, 0, 255); //Constrain light value
  analogWrite(RLED, val); //Control the LED
}
