/* OLED_HC_SR04_Animation
 * reference by
 * IDEA:  https://create.arduino.cc/projecthub/mircemk/diy-arduino-height-measuring-machine-0437dd
 * ANIMATION:  https://blog.naver.com/chandong83/221160691170
 * install library: newping, adafruit gfx, adafruit ssd1306
 * SDA A4, SCL A5, TRIG 9pin, ECHO 10pin
 */

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

NewPing sonar(9, 10, 200); // TRIG 9pin, ECHO 10pin
int base = 180;
int height;

/**************   애니메이션 시작  **************/
const int ANI_MODE_MOVE = 0; //이동 모드
const int ANI_MODE_WINK = 1; //윙크 모드

int preEyePos = 0; //이전 이미지 지우기 위한 눈 위치
int eyePos = 0;  //현재 이미지 그리기 위한 눈 위치
int eyeDir = 0;  //눈 움직이는 방향

int animationSpeed = 20; //애니메이션 딜레이

int animationMode = ANI_MODE_MOVE; //애니메이션 모드

long randNumber;

//윙크시 사용되는 변수
int preEyeHeight = 0;
int eyeHeight = 0;
int eyeHDir = 0;

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

  randomSeed(analogRead(0));
}

void loop()
{
  height = base - sonar.ping_cm();

  if (height < 0 || height > 180)
    height = 0;


  Serial.println(height);
  delay(20);

  if (height == 180)
    animation();
  else
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
  display.clearDisplay();
}

void animation(void) {  

  //윙크 모드로 동작
  animationMode = 0;

  //이전 눈 위치 갱신
  preEyePos = eyePos;

  //애니 속도는 1ms
  animationSpeed = 1;

  /**************   애니메이션 시작  **************/
  switch (animationMode) {
    case ANI_MODE_MOVE:
      //이전 눈 위치 값 저장
      //이전 그림 지우기 위함.
      preEyePos = eyePos;

      //눈 이동
      if (eyeDir == 0)
      {
        eyePos--;
        if (eyePos < 0)
        {
          eyePos = 0;
          eyeDir = 1;
        }
      }
      else
      {
        eyePos++;
        if (eyePos > 20)
        {
          eyePos = 20;
          eyeDir = 0;
        }
      }
      break;

    case ANI_MODE_WINK:
      //이전 눈 크기 값 저장
      preEyeHeight = eyeHeight;

      if (eyeHDir == 0) {
        eyeHeight++;
        if (eyeHeight > 10) {
          eyeHeight = 10;
          eyeHDir = 1;
        }
      } else {
        eyeHeight--;
        if (eyeHeight < 0) {
          eyeHeight = 0;
          eyeHDir = 0;

          //눈을 감았다가 뜨면 다시 이동
          animationMode = ANI_MODE_MOVE;
          animationSpeed = 20;
        }
      }
      break;
  }

  /**************   애니메이션 끝    **************/


  /**************   OLED 시작  **************/
  //왼쪽 눈
  display.drawRoundRect(preEyePos, 10 + preEyeHeight, 10, 20 - preEyeHeight, 5, BLACK);
  display.drawRoundRect(eyePos, 10 + eyeHeight, 10, 20 - eyeHeight, 5, WHITE);
  delay(animationSpeed);
  display.display();

  //오른쪽 눈
  display.drawRoundRect(preEyePos + 66, 10 + preEyeHeight, 10, 20 - preEyeHeight, 5, BLACK);
  display.drawRoundRect(eyePos + 66, 10 + eyeHeight, 10, 20 - eyeHeight, 5, WHITE);
  delay(animationSpeed);
  display.display();

  //입
  display.drawRoundRect(10, 50, (96 - 20), 14, 5, WHITE);
  display.drawLine(20, 57, 56 + 20, 57, WHITE);
  display.display();
  /**************   OLED 끝    **************/
}
