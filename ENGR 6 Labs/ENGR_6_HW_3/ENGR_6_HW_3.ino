/*
9/17/2025
Eric Chor

This program has a blinking RGB LED which toggles on
and off at regular intervals. There are two buttons, 
one button changes the color of the RGB LED, cycling
between 8 different options; the other button changes
the interval for when the RGB LED turns off and on.
*/
const int RED_LED = 3;
const int GREEN_LED = 10;
const int BLUE_LED = 9;
const int COLOR_BUTTON = 6;
const int TIMING_BUTTON = 4;
const int RX = 0;
const int TX = 1;

enum COLORS{
  red,
  green,
  blue,
  purple,
  teal,
  orange,
  white,
  clear
};

//set values for each RGB LED
void set_LED(int RED, int GREEN, int BLUE){
  analogWrite(RED_LED, RED);
  analogWrite(GREEN_LED, GREEN);
  analogWrite(BLUE_LED, BLUE);
}  

//debounces button by delaying 5 ms when button is pressed
bool debounce(int button, bool last_state){
  if(digitalRead(button) != last_state){
    delay(5);
  }
  //Serial.print("last:");
  //Serial.print(last_state);
  //Serial.print(" current: ");
  //Serial.println(digitalRead(button));
  return digitalRead(button);
}

//switch statement to change between different colors
void LED_COLOR (int color){
  //Serial.print("set color:");
  //Serial.println(color);
  switch (color){
    case red:
    	set_LED(255,0,0);
   		break;
    case green:
    	set_LED(0,255,0);
    	break;
    case blue:
    	set_LED(0,0,255);
    	break;
    case purple:
    	set_LED(127,0,255);
    	break;
    case teal:
    	set_LED(63,191,191);
    	break;
    case orange:
    	set_LED(255,127,127);
    	break;
    case white:
    	//set_LED(160,191,191);
      set_LED(255,255,255);
      break;
    case clear:
    	set_LED(0,0,0);
    	break;
  }
  
}    


int color_state = 0;
bool color_last = false;
bool timing_last = false;
bool light_state_on = true;
int current_limit_ms = 0;
//timer to create non-blocking delay
unsigned long last_timer = millis();

void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  
  pinMode(COLOR_BUTTON, INPUT);
  pinMode(TIMING_BUTTON, INPUT);
  Serial.begin(9600);
  LED_COLOR(color_state);
}
     
void loop()
{
  //whenever color button pressed: debounce button and increment state, if at the end of the states, cycle back
  if(digitalRead(COLOR_BUTTON) && (color_last==false)){
      if(debounce(COLOR_BUTTON,color_last) != color_last)
        if(color_state <7)
    		color_state ++;
        else
        	color_state = 0;
    	
      }
  
  //whenever timing button pressed: debounce button and increment state, if at the end of the states, cycle back
  if(digitalRead(TIMING_BUTTON) && (timing_last==false)){
      if(debounce(TIMING_BUTTON,timing_last) != timing_last)
        if(current_limit_ms < 2500)
    		current_limit_ms += 500;
        else
        	current_limit_ms = 0;
    	
      }
  
  //if the LED is supposed to be blinking turn the LED on and off using a timer
  if(current_limit_ms != 0){
    if((millis()-last_timer) > current_limit_ms){
      light_state_on = !light_state_on;
      last_timer = millis();
    } 
  } else {
      light_state_on = true;
  }
  
  //if the LED is supposed to be on write the values to LEDs based on the color state otherwise turn off all LEDs
  if(light_state_on){
    LED_COLOR(color_state);
  } else {
    LED_COLOR(clear);
  }
  
  //change last state of the buttons
  color_last = digitalRead(COLOR_BUTTON);
  timing_last = digitalRead(TIMING_BUTTON);
  
  // Serial.print("color : ");
  // Serial.print(digitalRead(COLOR_BUTTON));
  // Serial.print(" timing: ");
  // Serial.println(digitalRead(TIMING_BUTTON));
  
  //prints color state to the console for debugging
  Serial.print("Color state: ");
  Serial.print(color_state);
  //Serial.print("color last: ");
  //Serial.println(color_last);

  //prints time interval to console for debugging
  Serial.print(" time skip:");
  Serial.println(current_limit_ms);
  
  //delay 10 ms to save cpu resources
  delay(10);
}