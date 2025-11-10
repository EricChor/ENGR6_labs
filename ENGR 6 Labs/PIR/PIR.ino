const int LED=9;//The LED is connected to pin 9
const int PIR=2;//The PIR is connected to pin 2
void setup()
{
  pinMode (LED, OUTPUT);
  pinMode (PIR, INPUT);
  digitalWrite(LED,HIGH);
  delay (500);
  digitalWrite (LED,LOW);
  delay (500);
}
void loop()
{
  if (digitalRead(PIR) == LOW)
{
  digitalWrite(LED, LOW);
}else
{
  digitalWrite(LED, HIGH);
}
}