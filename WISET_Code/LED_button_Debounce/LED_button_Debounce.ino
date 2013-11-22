// 버튼으로 LED 깜빡이기(Debounce 예제)

int BUTTON = 7;  // 푸쉬버튼 핀 번호
int LED = 13;   // LED를 연결한 핀 번호

int val = 0;   // 버튼 상태를 저장하는 변수
int val_OLD = 0;
int State = 0; // 0: LED OFF, 1: LED ON

void setup() {
  pinMode(LED, OUTPUT);  // LED을 출력으로 설정    
  pinMode(BUTTON, INPUT);  // BUTTON을 입력으로 설정
}

void loop(){
  // 버튼을 입력하면 입력 값을 buttonstate에 저장
  val = digitalRead(BUTTON);
  
  if ( (val==HIGH) && (val_OLD==LOW) ) {
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
}

