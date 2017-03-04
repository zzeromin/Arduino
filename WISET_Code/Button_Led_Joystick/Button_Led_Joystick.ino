// 라즈판타스틱용 삼덕사 LED 버튼을 누르면 LED가 켜지는 예제

int buttonState[6] = {}; // 버튼 상태를 저장하는 변수

void setup()
{
  for (int i=8; i<=13; i++)
    pinMode(i, OUTPUT); // LED을 출력으로 설정
  for (int b=2; b<=7; b++)
    pinMode(b, INPUT); // BUTTON을 입력으로 설정  
}

void loop() {
  // 버튼을 누르면 입력 값을 buttonState에 저장
  for (int i=0; i<=5; i++) {
    buttonState[i] = digitalRead(i+2);
    LedButtonOnOff(buttonState[i], i+8);
  }
}

void LedButtonOnOff(int buttonState, int led)
{
  // 버튼을 눌렀을 때 버튼 상태가 HIGH면 LED를 켠다
  if (buttonState == HIGH) { 
    digitalWrite(led, HIGH); // LED를 켬    
  } 
  else {
    digitalWrite(led, LOW); // LED를 끔    
  } 
}
