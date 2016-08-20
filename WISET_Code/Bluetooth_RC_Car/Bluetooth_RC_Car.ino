#include <SoftwareSerial.h>

int TX = 2; // HC-06 TX pin
int RX = 3; // HC-06 RX pin

int IN1 = 4; // L298N pin setup
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

void motor_control(int i1, int i2, int i3, int i4);
// ENA, IN1, IN2, ENB, IN3, IN4

SoftwareSerial BTSerial(TX, RX);
// Connect HC-06 TX, RX

void setup()
{

  BTSerial.begin(9600);
  // set the data rate for the BT port

  for (int i = 4; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  if ( BTSerial.available() )  {
    switch ( BTSerial.read() ) {
      case 'F': //  Forward
        motor_control(1, 0, 1, 0);
        break;
      case 'B': // Backward
        motor_control(0, 1, 0, 1);
        break;
      case 'L': //  Left
        motor_control(1, 0, 0, 0);
        break;
      case 'R': //  Right
        motor_control(0, 0, 1, 0);
        break;
      case 'S': //  Stop
        motor_control(0, 0, 0, 0);
        break;
      default: //   Unknown
        break;
    }
  }
}
