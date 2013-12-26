/*
  LiquidCrystal Library - display() and noDisplay()
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD and uses the 
 display() and noDisplay() functions to turn on and off
 the display.
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe 
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/LiquidCrystalDisplay

*/

/* using SparkFun Inventor's Kit
74HC595 SHIFT REGISTER

  http://www.sparkfun.com/datasheets/IC/SN74HC595.pdf

Hardware connections:

  Shift register:
  
    Plug in the chip so it bridges the center "canyon"
    on the breadboard.
    
    The shift register has 16 pins. They are numbered
    counterclockwise starting at the pin 1 mark (notch
    in the end of the chip). See the datasheet above
    for a diagram.

    74HC595 pin		LED pin		Arduino pin
    
    1  (QB)		LED 2 +
    2  (QC)		LED 3 +
    3  (QD)		LED 4 +
    4  (QE)		LED 5 +
    5  (QF)		LED 6 +
    6  (QG)		LED 7 +
    7  (QH)		LED 8 +
    8  (GND)				GND
    
    9  (QH*)
    10 (SRCLR*)				5V
    11 (SRCLK)				Digital 3
    12 (RCLK)				Digital 4
    13 (OE*)				GND
    14 (SER)				Digital 2
    15 (QA)		LED 1 +
    16 (VCC)				5V
  
This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int BUTTON = 7;
int val = 0;
int val_OLD = 0;
int State = 0; // 0: LED OFF, 1: LED ON
int count = 0;

// Pin definitions:
// The 74HC595 uses a type of serial connection called SPI
// (Serial Peripheral Interface) that requires three pins:
int datapin = 8; 
int clockpin = 9;
int latchpin = 10;
int delayTime = 100;

// We'll also declare a global variable for the data we're
// sending to the shift register:
byte data = 0;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Welcome Italy");
  
  pinMode(BUTTON, INPUT);
  
  // Set the three SPI pins to be outputs:
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);
  
  for (int index = 0; index > 7; index++ ) {
    shiftWrite( index, LOW );
  }
}
void loop() {
  char *arr[8] = {"Welcome Italy", "Venezia", "Milano", "Torino", "Firenze", "ROMA", "Napoli", "Bari"};
  
  // 버튼을 입력하면 입력 값을 buttonstate에 저장
  val = digitalRead(BUTTON);
  
  if ( (val==HIGH) && (val_OLD==LOW) ) {
    State = 1 - State;
    count++;
    delay(10);
  }
  val_OLD = val;  
  
  Serial.println(count);
  delay(delayTime);
    
  if ( val == HIGH ) 
  {
    if ( count == 8 ) {
       count = 0;
       //shiftWrite( 7, LOW );
       //shiftWrite( 0, HIGH );
       for (int index = 0; index > 7; index++ ) {
          shiftWrite( index, HIGH );
       }
    } else {
      shiftWrite( count-1, LOW );
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(arr[count]);
      shiftWrite( count, HIGH );      
      delay(delayTime);
    }
  }
}

void shiftWrite(int desiredPin, boolean desiredState)

// This function lets you make the shift register outputs
// HIGH or LOW in exactly the same way that you use digitalWrite().

// Like digitalWrite(), this function takes two parameters:

//    "desiredPin" is the shift register output pin
//    you want to affect (0-7)

//    "desiredState" is whether you want that output
//    to be HIGH or LOW

// Inside the Arduino, numbers are stored as arrays of "bits",
// each of which is a single 1 or 0 value. Because a "byte" type
// is also eight bits, we'll use a byte (which we named "data"
// at the top of this sketch) to send data to the shift register.
// If a bit in the byte is "1", the output will be HIGH. If the bit
// is "0", the output will be LOW.

// To turn the individual bits in "data" on and off, we'll use
// a new Arduino commands called bitWrite(), which can make
// individual bits in a number 1 or 0.
{
  // First we'll alter the global variable "data", changing the
  // desired bit to 1 or 0:

  bitWrite(data,desiredPin,desiredState);
  
  // Now we'll actually send that data to the shift register.
  // The shiftOut() function does all the hard work of
  // manipulating the data and clock pins to move the data
  // into the shift register:

  shiftOut(datapin, clockpin, MSBFIRST, data);

  // Once the data is in the shift register, we still need to
  // make it appear at the outputs. We'll toggle the state of
  // the latchPin, which will signal the shift register to "latch"
  // the data to the outputs. (Latch activates on the high-to
  // -low transition).

  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}
