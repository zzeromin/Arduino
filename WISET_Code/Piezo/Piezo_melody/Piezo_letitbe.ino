/* Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/Tone    */

#include "pitches.h"

int melody[] = {
 NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, 
 NOTE_C5, NOTE_C5, NOTE_C5, NOTE_D5, 
 NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5,
 NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, 
 NOTE_G4, NOTE_G4, 
 NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_D5,
 NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5, NOTE_C5,
 NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_D5,
 NOTE_D5, NOTE_C5, NOTE_C5
  };

int noteDurations[] = {
  2, 2, 2, 2,
  2, 2, 2, 2, 
  2, 2, 2, 2,
  2, 4, 4, 1,
  8, 8,
  4, 8, 8, 4, 4, 4, 4, 8, 4, 
  8, 4, 4, 4, 4, 4, 4, 2,
  8, 2, 4, 4, 8, 4, 4, 8, 4, 
  4, 4, 1
};

void setup() {
  for (int thisNote = 0; thisNote < 45; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
