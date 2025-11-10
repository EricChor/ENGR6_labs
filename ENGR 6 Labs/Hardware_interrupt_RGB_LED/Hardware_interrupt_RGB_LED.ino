//Use Hardware-Debounced Switch to Control Interrupt
//Button pins
const int BUTTON_INT = 2;  //Interrupt 0 (pin 2 on the Uno) 
const int RED = 11;        //Red LED on pin 11
const int GREEN = 10;      //Green LED on pin 10
const int BLUE = 9;        //Blue LED on pin 9
//Volatile variables can change inside interrupts
volatile int selectedLED = RED;
void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  //The pin is inverted, so we want to look at the rising edge
  attachInterrupt(digitalPinToInterrupt(BUTTON_INT), swap, RISING);
}
void swap() {
  //turn off the previous LED before switching to the next one
  digitalWrite(selectedLED,0);
  //cycles through the LED whenever the interrupt is called
  if(selectedLED == BLUE){
    selectedLED = RED;
  } else {
    selectedLED--;
  }
}
void loop() {
  //fade in the LED brightness
  for (int i = 0; i < 256; i++) {
    analogWrite(selectedLED, i);
    delay(10);
  }
  //fade out the LED brightness
  for (int i = 255; i >= 0; i--) {
    analogWrite(selectedLED, i);
    delay(10);
  }
}
