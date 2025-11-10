/*
Eric Chor

10/11/2025

The purpose of this program is to detect motion using a PIR sensor;
when motion is detected a sound will play from the speaker and the 
servo will rotate to the occupied position. If there is no motion 
detected for 6 seconds then the servo will rotate back to the 
empty position.
*/

#include <Servo.h>
const int SPEAKER = A0;  //The LED is connected to pin 9
const int PIR = 2;      //The PIR is connected to pin 2
const int arrow_servo = 6;
unsigned long master_timer = 0;

const int sound_duration_timer = 500;
const int sound_replay_timer = 2000;
const int empty_timer = 30000; //5000 in the video so it is not so long
unsigned long last_timer = 0;
bool toggle_flag = false;
bool is_empty = true;

Servo POINTER_SERVO;

void setup() {
  Serial.begin(9600);
  pinMode(SPEAKER, OUTPUT);
  pinMode(PIR, INPUT);
  POINTER_SERVO.attach(arrow_servo);
}
void loop() {
  master_timer = millis();
  if((digitalRead(PIR) == LOW) && (master_timer > last_timer + sound_replay_timer)){
    toggle_flag = true;
  }

  if ((digitalRead(PIR) == HIGH) && (toggle_flag == true)){
    is_empty = false;
    Serial.print("motion detected-");
    Serial.println(digitalRead(PIR));
    toggle_flag = false;
    last_timer = master_timer;
    tone(SPEAKER,200);
    POINTER_SERVO.write(0);
    while(true){
      master_timer = millis();
      
      Serial.print(master_timer);
      Serial.print("::");
      Serial.print(last_timer);
      Serial.print("::");
      Serial.println(sound_duration_timer);
      if(master_timer > last_timer + sound_duration_timer)
        break;
    }
    noTone(SPEAKER);
    
  } else {
    Serial.print("no motion detected-");
    Serial.println(digitalRead(PIR));
    noTone(SPEAKER);
  }

  if(master_timer > last_timer + empty_timer){
    is_empty = true;
    POINTER_SERVO.write(180);
  }



}