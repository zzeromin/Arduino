// RFID reference: http://educ8s.tv/arduino-rfid-tutorial/
// OLED reference: https://github.com/adafruit/Adafruit_SSD1306

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

int code[] = {230, 156, 39, 249}; //This is the stored UID

int codeRead = 0;
String uidString;

int piezopin = 7;
int note[] = {2093, 2349, 2637, 2793, 3136, 3520, 3951, 4186}; //도레미파솔라시도
int relaypin = 6;

void setup()
{
  Serial.begin(9600); // 시리얼통신 초기화
  SPI.begin(); // SPI bus 초기화
  rfid.PCD_Init(); // MFRC522 초기화

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // OLED 초기화
  initOLED(); // OLED 초기화

  pinMode(relaypin, OUTPUT);
}

void loop()
{
  if ( rfid.PICC_IsNewCardPresent())
  {
    readRFID();
  }
  delay(100);
}

void readRFID()
{
  rfid.PICC_ReadCardSerial();
  Serial.print(F("\nPICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  Serial.println("Scanned PICC's UID:");
  printDec(rfid.uid.uidByte, rfid.uid.size);

  uidString = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);

  int i = 0;
  boolean match = true;
  while (i < rfid.uid.size)
  {
    if (!(rfid.uid.uidByte[i] == code[i]))
    {
      match = false;
    }
    i++;
  }

  if (match)
  {
    Serial.println("\nAuthenticated Card");
    digitalWrite(relaypin, HIGH);
    playSound();
    printUnlockMessage();    
  } else {
    Serial.println("\nUnknown Card");
    playBeep(100);    
    digitalWrite(relaypin, LOW);
    printLockMessage();
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}

void initOLED()
{
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE); // or BLACK);
  display.setTextSize(2);
  display.setCursor(40, 10);
  display.print("RFID");
  display.setCursor(5, 30);
  display.print("Switch Off");
  display.display();
}

void printUnlockMessage()
{
  display.display();
  display.setTextColor(BLACK); // or BLACK);
  display.setTextSize(2);
  display.setCursor(5, 30);
  display.print("Switch Off");
  display.display();

  display.setTextColor(WHITE); // or BLACK);
  display.setTextSize(2);
  display.setCursor(5, 30);
  display.print("Switch On");
  display.display();

  delay(3000);
}

void printLockMessage()
{
  display.setTextColor(BLACK); // or BLACK);
  display.setTextSize(2);
  display.setCursor(5, 30);
  display.print("Switch On");

  display.setTextColor(WHITE); // or BLACK);
  display.setTextSize(2);
  display.setCursor(5, 30);
  display.print("Switch Off");
  display.display();  
}

void playBeep(int delaytime)
{
  tone(piezopin, 500, delaytime); //500: 음의 높낮이(주파수), delaytime: 음의 지속시간(1000이면 1초)
  delay(20);
  noTone(piezopin);
}

void playSound()
{
  int elementCount = sizeof(note) / sizeof(int);
  for (int i = 0; i < elementCount; i++)
  {
    tone(piezopin, note[i], 500);
    delay(500);
    noTone(piezopin);
  }
}
