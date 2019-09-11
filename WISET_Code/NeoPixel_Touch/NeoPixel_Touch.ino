#include <Adafruit_NeoPixel.h>

#define LED1    4           // neopixel pin
#define LED2    5           // neopixel pin
#define LED3    6           // neopixel pin
#define LED_COUNT  64         // neopixel

Adafruit_NeoPixel strip1(LED_COUNT, LED1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED3, NEO_GRB + NEO_KHZ800);


int touchSensor = 7;
int val = 0;   // 버튼 상태를 저장하는 변수
int val_OLD = 0;
int State = 0; // 0: LED OFF, 1: LED ON

void setup() {
  Serial.begin(9600);
  strip1.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip1.show();            // Turn OFF all pixels ASAP
  strip1.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.show();            // Turn OFF all pixels ASAP
  strip2.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip3.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip3.show();            // Turn OFF all pixels ASAP
  strip3.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  pinMode(touchSensor, INPUT);
}

void loop() {
  int val = digitalRead(touchSensor);
  delay(20);

  Serial.print("Touch = ");
  Serial.print(val);
  Serial.print("  State = ");
  Serial.println(State);

  if ( (val == HIGH) && (val_OLD == LOW) ) {
    State = 1 - State;
    delay(10);
  }
  val_OLD = val;

  // 버튼을 눌렀을 때 버튼 상태가 HIGH면
  if (State == HIGH) {
    colorWipe(strip1.Color(255, 255, 0), 0); // Yellow
    colorWipe(strip2.Color(255, 255, 0), 0); // Yellow
    colorWipe(strip3.Color(255, 255, 0), 0); // Yellow
  }
  else {
    colorWipe(strip1.Color(0, 0, 0), 0); // off
    colorWipe(strip2.Color(0, 0, 0), 0); // off
    colorWipe(strip3.Color(0, 0, 0), 0); // off
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip1.numPixels(); i++) { // For each pixel in strip...
    strip1.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip1.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
  for (int i = 0; i < strip2.numPixels(); i++) { // For each pixel in strip...
    strip2.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip2.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
  for (int i = 0; i < strip3.numPixels(); i++) { // For each pixel in strip...
    strip3.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip3.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
