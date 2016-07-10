/*
** Simple spectrum analyzer for Arduino using MSGEQ7 and 16x2 I2C Character LCD with button
** This example uses F Malpartida's NewLiquidCrystal library. Obtain from:
** https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
** NOTE:
** Tested on Arduino Uno whose I2C pins are A4==SDA, A5==SCL
** Audio Input at A0, A1 Arduino Uno
** Original code at
** http://forum.arduino.cc/index.php?PHPSESSID=kqhsqkcl3dvshjeikkns3pio46&topic=214051.0
** http://tronixstuff.com/2013/01/31/tutorial-arduino-and-the-msgeq7-spectrum-analyzer/
** modified by zzeromin
** 버튼으로 VU_Meter, LEFT_RIGHT_VU_METER 변화
*/

#include <Wire.h>
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
LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

byte vumetro[8][8];
float vumeters[16];

// The analog pin 0 is used to read value.
int LCHAN = 0;
// The 4 & 5 pins are used for control the integrated.
int strobe = 4;
int reset = 5;
int left[7]; // store band values in these arrays
int right[7];

// LEFT, RIGHT VU Meters
// create custom characters for LCD
byte level1[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111};
byte level2[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111};
byte level3[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111};
byte level4[8] = { 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111};
byte level5[8] = { 0b00000, 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte level6[8] = { 0b00000, 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte level7[8] = { 0b00000, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
byte level8[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111};
int band;

// Button
int BUTTON = 3; // 푸쉬버튼 핀 번호
int val_BUTTON = 0; // 버튼 상태를 저장하는 변수
int val_OLD = 0; // 'val'의 이전 상태를 저장하는 변수
int State = 0; // 0이면 VU_Meter, 1이면 LEFT_RIGHT_VU_METER();

void setup()
{
  init_LCD();

  // Built the characters for bars.
  for (int j = 0; j <= 7; j++)
  {
    for (int i = 0; i <= 7; i++)
    {
      if (i <= j)
      {
        vumetro[j][7 - i] = B01110;
      }
      //      { vumetro[j][7-i] = B01010;}  Uncomment this lines for getting other variants for bars.
      //      { vumetro[j][7-i] = B11111;}
      else
      {
        vumetro[j][7 - i] = 0;
      }
    }
  }
  for (int i = 0; i <= 7; i++)
  {
    lcd.createChar(i, vumetro[i]);
  }

  for (int j = 0; j <= 7; j++)
  {
    lcd.setCursor(j, 0);
    lcd.write(j);
    lcd.setCursor(j, 1);
    lcd.write(7);

    pinMode(LCHAN, INPUT);
    pinMode(strobe, OUTPUT);
    pinMode(reset, OUTPUT);
    analogReference(DEFAULT);

    digitalWrite(reset, LOW);
    digitalWrite(strobe, HIGH);
  }
  pinMode(BUTTON, INPUT); // BUTTON을 입력으로 설정
}
void loop() {
  // 버튼을 입력하면 입력 값을 val에 상태를 저장
  val_BUTTON = digitalRead(BUTTON);
  // 입력 상태의 변화를 감지
  if ( (val_BUTTON == HIGH) && (val_OLD == LOW) ) {
    State = 1 - State;
    lcd.clear();
    delay(10);
  }
  val_OLD = val_BUTTON; // 이전 상태를 저장
  // 버튼을 눌렀을 때 버튼 상태가 HIGH면
  if (State == HIGH) {
    LEFT_RIGHT_VU_METER();
    // Show LEFT_RIGHT_VU_METER
  }
  else {
    VU_METER();
    // Show VU_METER
  }
}

void init_LCD() {
  lcd.begin (16, 2); //  <<----- My LCD was 16x2
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

  lcd.home(); // go home
  lcd.print(" VU METER TEST");
  lcd.setCursor(0, 1);       // go to start of 2nd line
  lcd.print(" I2C LCD 16x2");
  delay(500);
  lcd.clear();

  lcd.setCursor(0, 0);       // go to start of 2nd line
  lcd.print(" VU Meter Start");

  int i;
  for ( i = 1; i <= 8; i++ ) {
    lcd.setCursor(i, 1);
    lcd.write(i);
    delay(100);
  }
  for ( i = 1; i <= 8; i++ ) {
    lcd.setCursor(i + 8, 1);
    lcd.write(i);
    delay(100);
  }
  delay(500);
}

void readMSGEQ7()
// Function to read 7 band equalizers
{
  digitalWrite(reset, HIGH);
  digitalWrite(reset, LOW);

  // The read of integrated is done by multiplexing.
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(strobe, LOW);
    delayMicroseconds(5);
    left[i] = analogRead(LCHAN); // store left band reading
    right[i] = analogRead(1); // ... and the right
    digitalWrite(strobe, HIGH);
  }
}

void VU_METER()
{
  readMSGEQ7();

  // It's necesary to interpolate for calculating 16 bars having only 7 values read.
  for (int k = 0; k <= 15; k++)
  {
    switch (k)
    {
      case 0:
        vumeters[k] = left[0] / 64;
        break;

      case 1:
        vumeters[k] = (left[0] / 64 + left[1] / 64) / 2;
        break;

      case 2:
        vumeters[k] = left[1] / 64;
        break;

      case 3:
        vumeters[k] = (left[1] / 64 + left[2] / 64) / 2;
        break;

      case 4:
        vumeters[k] = left[2] / 64;
        break;

      case 5:
        vumeters[k] = (left[1] / 64 + left[2] / 64 + left[3] / 64) / 3;
        break;

      case 6:
        vumeters[k] = (left[2] / 64 + left[3] / 64 + left[4] / 64) / 3;
        break;

      case 7:
        vumeters[k] = random(2) + left[3] / 64;
        break;

      case 8:
        vumeters[k] = random(2) + left[3] / 64;
        break;

      case 9:
        vumeters[k] = (left[2] / 64 + left[3] / 64 + left[4] / 64) / 3;
        break;

      case 10:
        vumeters[k] = (left[3] / 64 + left[4] / 64 + left[5] / 64) / 3;
        break;

      case 11:
        vumeters[k] = left[4] / 64;
        break;

      case 12:
        vumeters[k] = (left[4] / 64 + left[5] / 64) / 2;
        break;

      case 13:
        vumeters[k] = left[5] / 64;
        break;

      case 14:
        vumeters[k] = (left[5] / 64 + left[6] / 64) / 2;
        break;

      case 15:
        vumeters[k] = left[6] / 64;
        break;
    }

    Dibuja_vumetro(k, vumeters[k]);
    delay(2);
  }
}

void Dibuja_vumetro(int posicion, int altura)
{
  if (altura > 7)
  {
    lcd.setCursor(posicion, 1);
    lcd.write(7);
    lcd.setCursor(posicion, 0);
    lcd.write(altura - 8);
  }
  else
  {
    lcd.setCursor(posicion, 1);
    lcd.write(altura);
    lcd.setCursor(posicion, 0);
    lcd.write(32);
  }
}

void LEFT_RIGHT_VU_METER()
{
  lcd.setCursor(0, 1);
  lcd.print("Left");
  lcd.setCursor(11, 1);
  lcd.print("Right");
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
