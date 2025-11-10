//Simple Motor Speed Control Program
const int MOTOR=9; //Motor on Digital Pin 9
float motor_power = 0;
void setup()
{
pinMode (MOTOR, OUTPUT);
}
void loop()
{
// ramp up the speed, delay 10 ms after write for motor to react
for(int i = 0; i<=100; i++){
  motor_power = i*1023/100;
  analogWrite(MOTOR,motor_power);
  delay(10);
}
delay(2000);

for(int i = 100; i>=0; i--){
  motor_power = i*1023/100;
  analogWrite(MOTOR,motor_power);
  delay(10);
}
analogWrite(MOTOR,0)
delay(2000);

// ramp down the speed, delay 10 ms after write for motor to react
}