//Use Hardware-Debounced Switch to Control Interrupt
//Button pins
const int COLOR_BUTTON = 2;  //Interrupt 0 (pin 2 on the Uno) 
const int DELAY_BUTTON = 3;  //Interrupt 1 (pin 3 on the Uno)

//pin definitions
const int RED_LED = 10;     
const int GREEN_LED = 9;    
const int BLUE_LED = 6;  

//check if the LED is supposed to be on or off
bool LED_ON = true;

//Volatile variables can change inside interrupts
volatile int selectedLED = red;
volatile int delay_time = 0;

//enumeration of the colors
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

//Write teh Values to the RGB LED
void set_LED(int RED, int GREEN, int BLUE){
  analogWrite(RED_LED, RED);
  analogWrite(GREEN_LED, GREEN);
  analogWrite(BLUE_LED, BLUE);
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
      set_LED(255,0,255);
      break;
    case teal:
      set_LED(127,127,255);
      break;
    case orange:
      set_LED(255,127,127);
      break;
    case white:
      set_LED(255,255,255);
    case clear:
      set_LED(0,0,0);
      break;
  }
 
}    

//function to switch colors when the button is pressed
void switch_color() {
  //cycles through the LED whenever the interrupt is called
  if(selectedLED == clear){
    selectedLED = red;
  } else {
    selectedLED++;
  }
  //writes the new colors to the LED
  LED_COLOR(selectedLED);
}

//changes the delay when the button is pressed
void switch_delay(){
  if(delay_time < 2500){
    delay_time += 500;
  } else {
    delay_time = 0;
  }

  //if the delay is set to 0 turn on the LED immediately
  if(delay_time ==0)
    LED_COLOR(selectedLED);
}


void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  //The pin is inverted, so we want to look at the rising edge
  attachInterrupt(digitalPinToInterrupt(COLOR_BUTTON), switch_color, RISING);
  attachInterrupt(digitalPinToInterrupt(DELAY_BUTTON), switch_delay, RISING);

  Serial.begin(9600);
}

void loop() {
  Serial.print("color : ");
  Serial.print(selectedLED);
  Serial.print(" delay : ");
  Serial.println(delay_time);

  //if the delay time is 0 turn on the LED
  if(delay_time == 0)
    LED_ON = true;

  //inverts the LED from on to off or off to on to blink
  if(delay_time != 0)
    LED_ON = !LED_ON;

  //If the LED is on write the color to the LED, if it is off turn off the LED
  if(LED_ON){
    LED_COLOR(selectedLED);
  } else {
    LED_COLOR(clear);
  }

  //pause for the delay time
  delay(delay_time);
}
