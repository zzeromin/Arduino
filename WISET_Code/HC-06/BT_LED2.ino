// control led with HC-06(bluethooth module)
// using Google Play app 'bluetooth serial controller'

#include <SoftwareSerial.h>

int ledpin = 13;
int TX = 2;
int RX = 3;

SoftwareSerial BTSerial(TX, RX);
// Connect HC-06 TX, RX

void setup()
{
  pinMode(ledpin, OUTPUT);
  BTSerial.begin(9600);
}

void loop()
{
  if (BTSerial.available()) {
    switch (BTSerial.read()) {
      case 'N':   digitalWrite(ledpin, HIGH);
        break;
      case 'F':   digitalWrite(ledpin, LOW);
        break;
      default:    digitalWrite(ledpin, LOW);
        break;
    }
  }
  delay(100);
}
