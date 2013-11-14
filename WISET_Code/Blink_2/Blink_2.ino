// LED 두 개를 깜빡이기(Blink 예제)

int LED1 = 6;  // LED1은 디지털 핀 6번 연결
int LED2 = 7;  // LED2는 디지털 핀 7번 연결

void setup()
{
  pinMode(LED1, OUTPUT); // LED1을 출력으로 설정
  pinMode(LED2, OUTPUT); // LED2를 출력으로 설정
}
void loop()
{
  digitalWrite(LED1, HIGH); // LED1을 켠다.
  delay(1000);            // 1초 동안 대기
  digitalWrite(LED1, LOW); // LED1을 끈다.
  delay(1000);            // 1초 동안 대기

  digitalWrite(LED2, HIGH); // LED1을 켠다.
  delay(1000);            // 1초 동안 대기
  digitalWrite(LED2, LOW); // LED1을 끈다.
  delay(1000);            // 1초 동안 대기
}

