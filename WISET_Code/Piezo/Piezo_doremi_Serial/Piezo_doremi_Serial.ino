#define NOTE_C7  2093
#define NOTE_D7  2349
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_G7  3136
#define NOTE_A7  3520
#define NOTE_B7  3951
#define NOTE_C8  4186

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if( Serial.available() > 0 )
  {
    int note = Serial.read();
    if(note == '1') tone(2, NOTE_C7);
    else if(note == '2') tone(2, NOTE_D7);
    else if(note == '3') tone(2, NOTE_E7);
    else if(note == '4') tone(2, NOTE_F7);
    else if(note == '5') tone(2, NOTE_G7);
    else if(note == '6') tone(2, NOTE_A7);
    else if(note == '7') tone(2, NOTE_B7);
    else if(note == '8') tone(2, NOTE_C8);
    else if(note == '0') noTone(2);   
    delay(300); 
    noTone(2);
  }
}
