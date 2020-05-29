#include <NewPing.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

NewPing sonar(9, 10, 200);
int base = 180;
int height;

void setup()
{
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
}

void loop()
{
  height = base - sonar.ping_cm();

  if (height < 0 || height > 180)
    height = 0;

  Serial.println(height);
  delay(20);

  printHeight();
}

void printHeight(void) {
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 5);            // Start at top-left corner
  display.println(F("HEIGHT"));

  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(20, 30);            // Start at top-left corner
  display.print(height);
  display.println(F("cm"));
  display.display();
  delay(2000);
}
