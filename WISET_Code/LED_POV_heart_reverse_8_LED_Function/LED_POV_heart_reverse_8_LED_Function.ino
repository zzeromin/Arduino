/*
  Title        : LED_POV_heart_reverse.ino
  Author       : zzeromin, member of Duksung Univ. WISE Center
  Creation Date: Dec 6, 2017
  Homepage     : http://wise.duksung.ac.kr
*/

void setup() {
  for ( int i = 4; i < 12; i++ ) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  ledPov( 1, 1, 0, 0, 1, 1, 1, 1 );
  ledPov( 1, 0, 0, 0, 0, 1, 1, 1 );
  ledPov( 0, 0, 0, 0, 0, 0, 1, 1 );
  ledPov( 1, 0, 0, 0, 0, 0, 0, 1 );
  ledPov( 1, 1, 0, 0, 0, 0, 0, 0 );
  ledPov( 1, 0, 0, 0, 0, 0, 0, 1 );
  ledPov( 0, 0, 0, 0, 0, 0, 1, 1 );
  ledPov( 1, 0, 0, 0, 0, 1, 1, 1 );
  ledPov( 1, 1, 0, 0, 1, 1, 1, 1 );
}

void ledPov(int led1, int led2, int led3, int led4, int led5, int led6, int led7, int led8)
{
  digitalWrite(4, led1);
  digitalWrite(5, led2);
  digitalWrite(6, led3);
  digitalWrite(7, led4);
  digitalWrite(8, led5);
  digitalWrite(9, led6);
  digitalWrite(10, led7);
  digitalWrite(11, led8);
  delay(3);
}
