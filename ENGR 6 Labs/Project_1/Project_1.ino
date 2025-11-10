/*
ENGR6

Eric Chor
Marcus Mendoza

The purpose of this code is to use an arduino uno to simulate a guitar,
pressing differet buttons causes different notes to play. There is also
a photosensor which, when blocked, plays a song
*/

const int C_BUTTON = 13;
const int C_SHARP_BUTTON = 12;
const int D_BUTTON = 11;
const int D_SHARP_BUTTON = 10;
const int E_BUTTON = 9;
const int F_BUTTON = 8;
const int F_SHARP_BUTTON = 7;
const int G_BUTTON = 6;
const int G_SHARP_BUTTON = 5;
const int A_BUTTON = 4;
const int A_SHARP_BUTTON = 3;
const int B_BUTTON = 2;

const int speaker = A0;
const int photoresistor = A1;

bool current_state_is_auto = false;
bool stop_song = false;
bool button_being_pressed = false;

enum NOTES{
  C,       //1
  C_SHARP, //2
  D,       //3
  D_SHARP, //4
  E,       //5
  F,       //6
  F_SHARP, //7
  G,       //8
  G_SHARP, //9
  A,       //10
  A_SHARP, //11
  B,       //12
  OFF      //13
};

// plays a specific note when the function is called
void play_note(NOTES note){
  switch (note){
    case C:
    	tone(speaker,130.81);
      //Serial.println("playing C");
    	break;
    case C_SHARP:
    	tone(speaker,138.59);
      //Serial.println("playing C sharp");
    	break;
    case D:
    	tone(speaker,146.83);
      //Serial.println("playing D");
    	break;
    case D_SHARP:
    	tone(speaker,155.56);
      //Serial.println("playing D sharp");
    	break;
    case E:
    	tone(speaker,164.81);
      //Serial.println("playing E");
    	break;
    case F:
    	tone(speaker,173.66);
      //Serial.println("playing F");
    	break;
    case F_SHARP:
    	tone(speaker,185.00);
      //Serial.println("playing F sharp");
    	break;
    case G:
    	tone(speaker,196.00);
      //Serial.println("playing G");
    	break;
    case G_SHARP:
    	tone(speaker,207.65);
      //Serial.println("playing G sharp");
    	break;
    case A:
    	tone(speaker,220.00);
      //Serial.println("playing A");
    	break;
    case A_SHARP:
    	tone(speaker,233.08);
      //Serial.println("playing A sharp");
    	break;
    case B:
    	tone(speaker,246.94);
      //Serial.println("playing B");
    	break;
    case OFF:
    	noTone(speaker);
    	break;
  }
}

//song notes to be played
NOTES notes []{D,D,C,C,B,B,A_SHARP,A_SHARP,
            	 D,D,C,C,B,B,A_SHARP,A_SHARP,
           		 D,D,C,C,B,B,A_SHARP,A_SHARP,
               D,D,C,C,B,B,A_SHARP,A_SHARP};	

//plays the song by iterating through the array and playing each note one at a time
//checks if a button is pressed between each note, if a button is pressed, stop the song from finishing
void play_song(){
  for(int i = 0 ; i < sizeof(notes)/sizeof(notes[0]) ; i++){
    play_note(notes[i]);
      delay(100);
    noTone(speaker);
      delay(25);
    stop_song = check_button_pressed();
    if(stop_song)
      break;
  }
  stop_song = false;
}

//Checks if a button is pressed, if the button is pressed play the note and stop the song from playing
bool check_button_pressed(){
  if(digitalRead(C_BUTTON)){
    play_note(C);
    stop_song = true;
    return true;
  } else if (digitalRead(C_SHARP_BUTTON)){
    play_note(C_SHARP);
    stop_song = true;
    return true;
  } else if (digitalRead(D_BUTTON)){
    play_note(D);
    stop_song = true;
    return true;
  } else if (digitalRead(D_SHARP_BUTTON)){
    play_note(D_SHARP);
    stop_song = true;
    return true;
  } else if (digitalRead(E_BUTTON)){
    play_note(E);
    stop_song = true;
    return true;
  } else if (digitalRead(F_BUTTON)){
    play_note(F);
    stop_song = true;
    return true;
  } else if (digitalRead(F_SHARP_BUTTON)){
    play_note(F_SHARP);
    stop_song = true;
    return true;
  } else if (digitalRead(G_BUTTON)){
    play_note(G);
    stop_song = true;
    return true;
  } else if (digitalRead(G_SHARP_BUTTON)){
    play_note(G_SHARP);
    stop_song = true;
    return true;
  } else if (digitalRead(A_BUTTON)){
    play_note(A);
    stop_song = true;
    return true;
  } else if (digitalRead(A_SHARP_BUTTON)){
    play_note(A_SHARP);
    stop_song = true;
    return true;
  } else if (digitalRead(B_BUTTON)){
    play_note(B);
    stop_song = true;
    return true;
  } else {
    play_note(OFF);
    return false;
  }
}

//initialize all pins to input except for the speaker which is initialized to output
void setup()
{
  Serial.begin(9600);
  pinMode(C_BUTTON,INPUT);
  pinMode(C_SHARP_BUTTON, INPUT);
  pinMode(D_BUTTON, INPUT);
  pinMode(E_BUTTON, INPUT);
  pinMode(F_BUTTON, INPUT);
  pinMode(F_SHARP_BUTTON, INPUT);
  pinMode(G_BUTTON, INPUT);
  pinMode(G_SHARP_BUTTON, INPUT);
  pinMode(A_BUTTON, INPUT);
  pinMode(A_SHARP_BUTTON, INPUT);
  pinMode(B_BUTTON, INPUT);
 	
  pinMode(speaker,OUTPUT);
  pinMode(photoresistor, INPUT);
  
}

void loop()
{
  
  //checks the value of the photoresistor, if it is low enough then play the song
  if(analogRead(photoresistor)<30){
    current_state_is_auto = true;
  } else {
    current_state_is_auto = false;
  }
  
  //Serial.println(analogRead(photoresistor));
  
  //check if any buttons are being pressed, if any buttons are being pressed play the note
  button_being_pressed = check_button_pressed();
  if((current_state_is_auto)&&(!button_being_pressed)){
       play_song();

  }
  delay(10);
  
}