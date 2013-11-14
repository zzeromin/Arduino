// 02. 버튼으로 LED 깜빡이기(Button 예제)

const int buttonPin = 2;  // 푸쉬버튼 핀 번호
const int ledPin =  13;   // LED를 연결한 핀 번호

int buttonState = 0;   // 버튼 상태를 저장하는 변수

void setup() {
  pinMode(ledPin, OUTPUT);  // ledPin을 출력으로 설정    
  pinMode(buttonPin, INPUT);  // buttonPin을 입력으로 설정
}


void loop(){
  // 버튼을 입력하면 입력 값을 buttonstate에 저장
  buttonState = digitalRead(buttonPin);

  // 버튼을 눌렀을 때 버튼 상태가 HIGH면
  if (buttonState == HIGH) {     
    digitalWrite(ledPin, HIGH);  // LED를 켬
  } 
  else {
    digitalWrite(ledPin, LOW); // LED를 끔
  }
}
