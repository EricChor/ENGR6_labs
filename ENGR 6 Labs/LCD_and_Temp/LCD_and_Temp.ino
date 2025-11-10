/*
Eric Chor

10/29/2025

The purpose of this code is to read the temperature from a TC74 temperature sensor
using the I2C protocol. The temperature value is sent in degrees celsius and two buttons
will allow the user to change between printing the result in Celsius and printing the result
in farenheight.

*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int farenheight_button = 3;
const int celsius_button = 4;
//Variable to store if the current result displayed on the screen is celsius (true) or farenheight (false)
bool is_celsius = true;

//I2C address of the TC74
int temp_address = 72;  //1001000 written as decimal number
void setup() {
  //Start serial communication at 9600 baud
  Serial.begin(9600);
  //initialize the LCD and turns on the back light to make it easier to see the text
  lcd.init();
  lcd.backlight();
  lcd.print("starting setup");
  //Create a Wire object
  Wire.begin();
  //set ups the two pins
  pinMode(farenheight_button, INPUT);
  pinMode(celsius_button, INPUT);
}
void loop() {
  //Send a request
  //Start talking to the device at the specified address
  Wire.beginTransmission(temp_address);
  //Send a bit asking for register zero, the data register
  Wire.write(0);
  //Complete Transmission
  Wire.endTransmission();
  //Read the temperature from the device
  //Request 1 Byte from the specified address
  Wire.requestFrom(temp_address, 1);
  //Wait for response
  while (Wire.available() == 0) {
    Serial.println("no data");
    delay(500);
  }
  //Get the temp and read it into a variable
  int c = Wire.read();
  //Do some math to convert the Celsius to Fahrenheit
  int f = round(c * 9.0 / 5.0 + 32.0);

  //clears the LCD screen then checks if a button is being pressed, based on the button pressed check if the result should be in celsius or Farenheight
  lcd.clear();
  if (digitalRead(celsius_button)) {
    is_celsius = true;
  }
  if (digitalRead(farenheight_button)) {
    is_celsius = false;
  }

  //If the format is supposed to be in Celsius, print the result in Celsius, if the format is supposed to be in farenheight, print the result in farenheight
  if (is_celsius) {
    lcd.print("C: ");
    lcd.print(c);
    Serial.print("C");
  } else {
    lcd.print("F: ");
    lcd.print(f);
    Serial.print("F");
  }

  //Send the temperature in degrees C and F to the serial monitor to make debuggin easier
  Serial.print(digitalRead(celsius_button));
  Serial.print(" ");
  Serial.println(digitalRead(farenheight_button));
  // Serial.print(c);
  // Serial.print("C ");
  // Serial.print(f);
  // Serial.println("F");
  delay(10);
}