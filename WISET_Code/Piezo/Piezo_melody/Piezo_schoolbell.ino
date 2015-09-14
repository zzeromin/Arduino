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
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4,
  NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, 0,  
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_E4,
  NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_C4, 0 
  };

int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 2, 4,
  4, 4, 4, 4, 4, 4, 2, 
  4, 4, 4, 4, 2, 4
};

void setup() {
  for (int thisNote = 0; thisNote < 26; thisNote++) {

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
