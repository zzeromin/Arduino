#include <SoftwareSerial.h>

int TX = 2;
int RX = 3;

int IN1 = 4;
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
    if (BTSerial.available()) {
        switch (BTSerial.read()){
            case 'F': //  Serial.println("Forward");
                        motor_control(1, 0, 1, 0);                        
                        break;
            case 'B': //  Serial.println("Backward");
                        motor_control(0, 1, 0, 1);                        
                        break;
            case 'L'://   Serial.println("Left");
                        motor_control(1, 0, 0, 0);
                        break;
            case 'R'://   Serial.println("Right");
                        motor_control(0, 0, 1, 0);
                        break;
            case 'S'://   Serial.println("Stop");
                        motor_control(0, 0, 0, 0);                       
                        break;
            default: //   Serial.println("Unknown");
                        break;
        }
    }
}

void motor_control(int i1, int i2, int i3, int i4)
{
    digitalWrite(IN1, i1);
    digitalWrite(IN2, i2);    
    digitalWrite(IN3, i3);
    digitalWrite(IN4, i4);
}
