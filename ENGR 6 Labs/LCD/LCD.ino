//LCD text with incrementing number
//Include the library code:
#include <LiquidCrystal_I2C.h>
const int LCD_button = A0;
//Start the time at 0
int time = 0;
int read_value = 0;
int state = 5; //0 = up | 1 = right | 2 = down | 3 = left | 4 = switch 
const int bound = 20;
//Initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 16, 2); 
void setup()
{
  //Set up the LCD's number of columns and rows:
  lcd.init();
  lcd.backlight();
  lcd.print("test");
  
}
void loop() {
  read_value = analogRead(LCD_button);
  lcd.clear();
  lcd.print(read_value);
  if(abs((read_value-745)) < bound){
    state = 4; //switch
  } else if (abs((read_value-190)) < bound){
    state = 1; //right
  } else if (abs((read_value-135)) < bound){
    state = 0; //up
  } else if (abs((read_value-405)) < bound){
    state = 2; //down
  } else if (abs((read_value-535)) < bound){
    state = 3; //left
  } 
  if(state == 0){
    lcd.print("up");
  } else if (state == 1){
    lcd.print("right");
  } else if (state == 2){
    lcd.print("down");
  } else if(state == 3){
    lcd.print("left");
  } else if (state == 4){
    lcd.print("switch");
  }

  delay(500);
}