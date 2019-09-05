#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

int touchSensor = 7;
int LED = 6;
int val = 0;   // 버튼 상태를 저장하는 변수
int val_OLD = 0;
int State = 0; // 0: LED OFF, 1: LED ON

int volume = 15;
void playMusic(int vol, int i);
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

#define CARD1 "DA 5D 55 17" // 1번카드
#define CARD2 "35 88 86 4B" // 2번카드

void setup() {
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                           // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(1);       // value 0~30

  pinMode(touchSensor, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {

  int val = digitalRead(touchSensor);
  if ( (val == HIGH) && (val_OLD == LOW) ) {
    State = 1 - State;
    delay(10);
  }
  val_OLD = val;

  // 버튼을 눌렀을 때 버튼 상태가 HIGH면
  if (State == HIGH) {
    digitalWrite(LED, HIGH);  // LED를 켬
  }
  else {
    digitalWrite(LED, LOW); // LED를 끔
  }

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  //Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  //Serial.println();
  //Serial.print("Message : ");

  content.toUpperCase();
  if (content.substring(1) == CARD1) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("1");
    playMusic(volume, 1);
    delay(20);
  } else if (content.substring(1) == CARD2) {
    Serial.println("2");
    playMusic(volume, 2);
    delay(20);
  } else {
    Serial.println("0"); //Access denied.
    myDFPlayer.stop();
    delay(20);
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void playMusic(int vol, int i)
{
  myDFPlayer.volume(vol);  //Set volume value. From 0 to 30
  myDFPlayer.play(i);  //Play the first mp3
}
