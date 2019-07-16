// RFID reference: http://educ8s.tv/arduino-rfid-tutorial/
// OLED reference: https://github.com/adafruit/Adafruit_SSD1306

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {

  Serial.begin(9600);  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(10, 0);
  display.print("Hello World");
  display.display();
  
  Serial.println("Hello World");
}

void loop() {
    
}
