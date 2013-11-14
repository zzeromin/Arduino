// 3색 신호등 만들기(LED, Button 활용 프로젝트)

int r_led = 12; // 빨강 LED 12번 핀 사용
int y_led = 11; // 노랑 LED 11번 핀 사용
int g_led = 10; // 녹색 LED 10번 핀 사용

int button = 2; // 버튼 2번 핀 사용
int button_state = 0; // 버튼 상태 저장 변수

void setup(){
  // LED는 출력, 버튼은 입력으로 사용
  pinMode(r_led, OUTPUT);
  pinMode(y_led, OUTPUT);
  pinMode(g_led, OUTPUT);
  pinMode(button, INPUT);
}

void loop()
{
  button_state = digitalRead(button); // 버튼 입력 상태 확인

  // 버튼을 누르지 않은 상태면 빨강 LED 켜짐
  if (button_state == LOW) {
    digitalWrite(r_led, HIGH); // 
    digitalWrite(y_led, LOW);  // 
    digitalWrite(g_led, LOW);  // 
  }
  else { // 버튼을 누르면 노랑색 1초, 녹색 3초 켜짐
    digitalWrite(r_led, LOW); // 
    digitalWrite(y_led, HIGH); // 
    delay(1000);
    digitalWrite(y_led, LOW); // 
    digitalWrite(g_led, HIGH);  // 
    delay(3000);
  }
}

