/*
** VU Meter for Arduino using MSGEQ7 and 0.96 128x64 OLED Display
** reference: http://www.instructables.com/id/OLED-Spectrum-Analyzer-Warduino-MSGEQ7/
** This example uses Adafruit library. Obtain from:
** https://github.com/adafruit/Adafruit-GFX-Library
** https://github.com/adafruit/Adafruit_SSD1306
** https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
** NOTE:
** Tested on Arduino Uno whose I2C pins are A4==SDA, A5==SCL
** Audio Input at A0, A1 Arduino Uno
** Original code at
** modified by zzeromin
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int strobe = 4; // strobe pins on digital 4
int res = 5; // reset pins on digital 5
int left[7]; // store band values in these arrays
int right[7];
int band;
int sens;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

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
  for (band = 0; band < 7; band++)
  {
    digitalWrite(strobe, LOW); // strobe pin on the shield - kicks the IC up to the next band
    delayMicroseconds(30); //
    sens = map(analogRead(A1), 0, 1023, 200, 1023);
    left[band] = map(analogRead(0), 100, sens, 0, 32); // store left band reading
    digitalWrite(strobe, HIGH);
  }
}
void loop()
{
  readMSGEQ7();
  // you can use function of Rectangles
  // drawRect or fillRect
  display.drawRect(0, 0, 10, left[0], WHITE);
  display.drawRect(20, 0, 10, left[1], WHITE);
  display.drawRect(40, 0, 10, left[2], WHITE);
  display.drawRect(60, 0, 10, left[3], WHITE);
  display.drawRect(80, 0, 10, left[4], WHITE);
  display.drawRect(100, 0, 10, left[5], WHITE);
  display.drawRect(120, 0, 8, left[6], WHITE);
  display.display();
  display.clearDisplay();
}
