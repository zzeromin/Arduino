#include  <SoftwareSerial.h>

//  SoftwareSerial(RX, TX)  형식으로  블루투스  모듈과  교차하여  연결된다.
// HC-06의 TX를 아두이노의 2(RX)번에 연결
// HC-06의 RX를 아두이노의 3(TX)번에 연결
SoftwareSerial  BTSerial(2,  3); 

void  setup()  
{
  Serial.begin(9600);
  BTSerial.begin(9600); //  블루투스  모듈  통신  속도의  디폴트값
}

void  loop()
{
  //  블루투스  모듈  -->  아두이노  -->  시리얼  모니터
  if  (BTSerial.available())
  Serial.write(BTSerial.read());
  
  //  시리얼  모니터  -->  아두이노  -->  블루투스  모듈
  if  (Serial.available())
  BTSerial.write(Serial.read());
}
