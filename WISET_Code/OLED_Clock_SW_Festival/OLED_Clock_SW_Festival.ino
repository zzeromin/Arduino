/*
  Title        : OLED_Clock_SW_Festival.ino
  Author       : zzeromin, member of Duksung Univ. WISE Center
  Creation Date: Nov 24, 2017
  Homepage     : http://wise.duksung.ac.kr
*/

/***************************************************************
  OLED Analogue Clock using Adafruit GFX and OLED libraries
  by Chris Rouse Oct 2014
  visit https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples
  for the OLED libraries and instructions on their use.

  Using a IIC 128x64 OLED with SSD1306 chip
  RTC DS1307
  Wire RTC:
  SCL Analog pin 5
  SDA Analog pin 4
  GND GND
  VCC +5v
***************************************************************/
// Add libraries
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// setup OLED display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Setup RTC
RTC_DS1307 RTC;
char monthString[37] = {"JanFebMarAprMayJunJulAugSepOctNovDec"};
int  monthIndex[122] = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33};

int led = 2;
int button = 3;
int buttonState = 0;
int speakerPin = 11;

//Jingle Bells
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
int tempo = 200;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(speakerPin, OUTPUT);

  // If you want to set the aref to something other than 5v
  // analogReference(EXTERNAL);
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    // Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  // Use I2C Scanner to check the address, if necessary change the 0x3C in the line below
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done
  // set font size
  display.setTextSize(2.5);  // small font size
  display.setTextColor(WHITE);
  display.clearDisplay();
}

void loop() {
  ledBlink();
  buttonInput();

  //***** RTC **********
  DateTime now = RTC.now();
  display.setCursor(0, 5);
  display.setTextSize(2);  // small font size
  display.print(now.year(), DEC);
  display.print(' ');
  for (int i = 0; i <= 2; i++) {
    display.print(monthString[monthIndex[now.month() - 1] + i]);
  }
  //display.print(' ');
  display.print(now.day(), DEC);

  // display time in digital format
  display.setCursor(5, 30);
  display.setTextSize(4);  // small font size
  display.print(now.hour(), DEC);
  printDigits(now.minute());

  // update display with all data
  display.display();
  display.clearDisplay();
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  display.print(":");
  if (digits < 10)
    display.print('0');
  display.print(digits);
}

void ledBlink() {
  int delaytime = 400;
  digitalWrite(led, HIGH);
  delay(delaytime);
  digitalWrite(led, LOW);
  delay(delaytime);
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
  int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void buttonInput() {
  buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    playCarol();
  } else {
    //noTone(speakerPin);
  }
}

void playCarol() {
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    // pause between notes
    delay(tempo / 2);
  }
}
