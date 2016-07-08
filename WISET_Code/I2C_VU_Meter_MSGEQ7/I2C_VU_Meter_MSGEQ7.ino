/* 
** Simple spectrum analyzer for Arduino using MSGEQ7 and 16x2 I2C Character LCD
** This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
** https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
** NOTE:
** Tested on Arduino Uno whose I2C pins are A4==SDA, A5==SCL
** Audio Input at A0, A1 Arduino Uno
** modified by zzeromin
*/
// Original code at Example 48.2 - tronixstuff.com/tutorials > chapter 48 - 30 Jan 2013
// MSGEQ7 spectrum analyser shield and I2C LCD from akafugu
// for akafugu I2C LCD

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

// create custom characters for LCD
byte level1[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111};
byte level2[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111};
byte level3[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111};
byte level4[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111};
byte level5[8] = { 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte level6[8] = { 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte level7[8] = { 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte level8[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
int strobe = 4; // strobe pins on digital 4
int res = 5; // reset pins on digital 5
int left[7]; // store band values in these arrays
int right[7];
int band;

void setup()
{
  // setup LCD and custom characters
  lcd.begin(16, 2);
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.clear();
  lcd.createChar(1, level1);
  lcd.createChar(2, level2);
  lcd.createChar(3, level3);
  lcd.createChar(4, level4);
  lcd.createChar(5, level5);
  lcd.createChar(6, level6);
  lcd.createChar(7, level7);
  lcd.createChar(8, level8);

  lcd.setCursor(0, 1);
  lcd.print("Left");
  lcd.setCursor(11, 1);
  lcd.print("Right");
  pinMode(res, OUTPUT); // reset
  pinMode(strobe, OUTPUT); // strobe
  digitalWrite(res, LOW); // reset low
  digitalWrite(strobe, HIGH); //pin 5 is RESET on the shield
}
void readMSGEQ7()
// Function to read 7 band equalizers
{
  digitalWrite(res, HIGH);
  digitalWrite(res, LOW);
  for ( band = 0; band < 7; band++ )
  {
    digitalWrite(strobe, LOW); // strobe pin on the shield - kicks the IC up to the next band
    delayMicroseconds(30); //
    left[band] = analogRead(0); // store left band reading
    right[band] = analogRead(1); // ... and the right
    digitalWrite(strobe, HIGH);
  }
}
void loop()
{
  readMSGEQ7();
  // display values of left channel on LCD
  for ( band = 0; band < 7; band++ )
  {
    lcd.setCursor(band, 0);
    if (left[band] >= 895) {
      lcd.write(8);
    } else if (left[band] >= 767) {
      lcd.write(7);
    } else if (left[band] >= 639) {
      lcd.write(6);
    } else if (left[band] >= 511) {
      lcd.write(5);
    } else if (left[band] >= 383) {
      lcd.write(4);
    } else if (left[band] >= 255) {
      lcd.write(3);
    } else if (left[band] >= 127) {
      lcd.write(2);
    } else if (left[band] >= 0) {
      lcd.write(1);
    }
  }

  // display values of right channel on LCD
  for ( band = 0; band < 7; band++ )
  {
    lcd.setCursor(band + 9, 0);
    if (right[band] >= 895) {
      lcd.write(8);
    } else if (right[band] >= 767) {
      lcd.write(7);
    } else if (right[band] >= 639) {
      lcd.write(6);
    } else if (right[band] >= 511) {
      lcd.write(5);
    } else if (right[band] >= 383) {
      lcd.write(4);
    } else if (right[band] >= 255) {
      lcd.write(3);
    } else if (right[band] >= 127) {
      lcd.write(2);
    } else if (right[band] >= 0) {
      lcd.write(1);
    }
  }
}
