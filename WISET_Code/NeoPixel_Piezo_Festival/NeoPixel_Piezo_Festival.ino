/*
  Title        : NeoPixel_Piezo_Touch.ino
  Author       : zzeromin, member of Raspberrypi Village and Tentacle Team
  Creation Date: Aug 5, 2017
  Blog         : http://rasplay.org, http://forums.rasplay.org/, https://zzeromin.tumblr.com/
  Github       : https://github.com/rasplay, https://github.com/zzeromin
  Cafe         : http://cafe.naver.com/raspigamer
  reference    : https://kocoafab.cc/tutorial/view/461
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
const int knock = A5;
int sensorVal = 0;
int count = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  //  Serial.begin(9600);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  colorWipe(strip.Color(0, 0, 0), 20); // led off
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  //노크 센서 값이 10보다 작을 동안에는 아무 것도 하지 않는다.
  waiting();

  // rainbowCamp(sensorVal + 50);

  switch ( count ) {
    case 0:
      colorWipe(strip.Color(0, 0, 0), 20); // led off
      delay(20);
      break;
    case 1:
      colorWipe(strip.Color(150, 0, 255), 20); // Violet
      delay(20);
      break;
    case 2:
      colorWipe(strip.Color(0, 255, 0), 20); // Green
      delay(20);
      break;
    case 3:
      colorWipe(strip.Color(0, 0, 255), 20); // Blue
      delay(20);
      break;
    case 4:
      colorWipe(strip.Color(255, 255, 0), 20); // Yellow
      delay(20);
      break;
    case 5:
      colorWipe(strip.Color(255, 255, 255), 20); // White
      delay(20);
      break;
    case 6:
      rainbow(15);
      break;
    default:
      colorWipe(strip.Color(0, 0, 0), 20); // led off
      delay(20);
      break;

  }

  /*
    // Some example procedures showing how to display to the pixels:
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
    //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
    // Send a theater pixel chase in...
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127, 0, 0), 50); // Red
    theaterChase(strip.Color(0, 0, 127), 50); // Blue

    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);
  */
}

void waiting(void) {
  while ((sensorVal = analogRead(knock)) < 20) {
  }  

  tone(knock, 2093, 100);
  delay(250);

  //소리 정지 후 다시 input으로 전환
  noTone(knock);
  pinMode(knock, INPUT);
  count++;
  if ( count == 7 )
    count = 0;
  delay(300);
  
  // 센서 값이 10이상이면 센서 값을 출력  
  Serial.print(sensorVal);
  Serial.print(" knock");
  Serial.print("    count = ");
  Serial.println(count);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbowCamp(int output) {
  uint16_t i;

  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((output) & 255));
    strip.show();
    delay(20);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  while ( (sensorVal = analogRead(knock)) < 10 ) {
    for (j = 0; j < 256; j++) {
      if ( ( sensorVal = analogRead(knock) ) < 10 ) {
        for (i = 0; i < strip.numPixels(); i++)
          strip.setPixelColor(i, Wheel((i + j) & 255));
        strip.show();
        delay(wait);
      } else break;
    }
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
