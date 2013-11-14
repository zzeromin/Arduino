// 1. LED 깜빡이기(Blink 예제)

int LED = 13;  //LED는 디지털 핀 13번 연결

void setup()
{
  pinMode(LED, OUTPUT); //디지털핀을 출력으로 설정
}
void loop()
{
  digitalWrite(LED, HIGH); //LED를 켠다
  delay(1000);            //1초동안 대기
  digitalWrite(LED, LOW); //LED를 끈다
  delay(1000);            //1초동안 대기
}
