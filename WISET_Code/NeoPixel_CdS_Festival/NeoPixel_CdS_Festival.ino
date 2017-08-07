/*
Title        : NeoPixel_CdS_Festival.ino
Author       : zzeromin, member of Raspberrypi Village and Tentacle Team
Creation Date: Aug 5, 2017
Blog         : http://rasplay.org, http://forums.rasplay.org/, https://zzeromin.tumblr.com/
Github       : https://github.com/rasplay, https://github.com/zzeromin
Cafe         : http://cafe.naver.com/raspigamer
*/

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // delay for half a second
int input;
int output;
int count;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  //pixels.begin(); // This initializes the NeoPixel library.
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {

  int waiting;
  int basicDelay = 500;
  valuePrint();

  while ( count == 0 ) {
    sensorRead(basicDelay);
    valuePrint();
    colorWipe(strip.Color(150, 0, 255), 20); // Violet
    delay(20);    
  }

  while ( count == 1 ) {
    sensorRead(basicDelay);
    valuePrint();
    colorWipe(strip.Color(0, 255, 0), 20); // Green
    delay(20);
  }

  while ( count == 2 ) {
    sensorRead(basicDelay);
    valuePrint();
    colorWipe(strip.Color(0, 0, 255), 20); // Blue
    delay(20);
  }
  
  while ( count == 3 ) {
    sensorRead(basicDelay);
    valuePrint();
    colorWipe(strip.Color(255, 255, 0), 20); // Yellow
    delay(20);
  }
  
  while ( count == 4 ) {
    sensorRead(basicDelay);
    valuePrint();
    rainbow(15);
    //rainbowCycle(20);
    //theaterChaseRainbow(15);
    delay(20);
  }

  while ( count == 5 ) {
    sensorRead(basicDelay);
    valuePrint();
    colorWipe(strip.Color(0, 0, 0), 20);
    delay(20);
  }
}

void valuePrint(void) {
  Serial.print("Sensor = ");
  Serial.print(output);
  Serial.print("   Count = ");
  Serial.println(count);
  delay(10);
}

void sensorRead(int waiting) {
  input = analogRead(A5);
  output = map(input, 0, 1023, 0, 254);
  if ( output < 20 ) {
    count++;
    if ( count == 6 ) {
      count = 0;
      delay(500);
      }
  }
  delay(waiting);
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    sensorRead(10);
    if ( count != 4 ) {
      delay(500);
      break;
    }
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

