/*
  9/24/2025

  Eric Chor

  The purpose of this program is to play scales in different octaves. The program
  cycles through all of the scales in a specific octave, pauses for a moment, then
  cycles through all of the scales in the next higher octave.

*/
#include "pitches.h" //Header file with pitch definitions
const int SPEAKER=9; //Speaker Pin


int scale[] = {NOTE_B0,NOTE_C1,NOTE_CS1,NOTE_D1,NOTE_DS1,NOTE_E1,
               NOTE_F1,NOTE_FS1,NOTE_G1,NOTE_GS1,NOTE_A1,NOTE_AS1};
void setup()
{
}
void loop()
{
  for (int octave = 0; octave < 8; octave++){
    for(int scale_number = 0; scale_number < sizeof(scale)/sizeof(scale[0]); scale_number++){
      tone(SPEAKER,scale[scale_number]*pow(2,octave));
      delay(100);
      noTone(SPEAKER);
      delay(25);
    }
    delay(500);
  }
}