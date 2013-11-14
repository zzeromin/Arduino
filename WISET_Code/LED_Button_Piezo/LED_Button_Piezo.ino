int BUTTON = 8; // 버튼 핀 번호
int PIEZO = 9;   // 피에조스피커 핀 번호
int LED = 13;    // LED 핀 번호

int val = 0;     // val은 입력 핀의 상태 저장 변수
int freq = 0;    // 주파수값 저장 변수

void setup()
{
  pinMode(LED, OUTPUT);   // LED는 출력
  pinMode(PIEZO, OUTPUT); //  PIEZO는 출력
  pinMode(BUTTON, INPUT); // BUTTON은 입력
  Serial.begin(9600); // 시리얼 통신 설정
}
void loop()
{
  val = digitalRead(BUTTON); // 입력 값을 읽어 저장
  // 입력이 HIGH (버튼이 눌림) 인지 검사
  if ( val == HIGH ) {
    digitalWrite(LED, HIGH);
    tone(PIEZO, freq, 1000); 
    freq = freq+50; //반복될수록 50Hz 증가
    delay(1000);
    if( freq == 4000 ) 
      freq = 0;
    Serial.println(freq); // 시리얼 모니터에 주파수값 출력
   } 
  else {
    freq = 0;    // 주파수를 0으로 되돌림
    tone(PIEZO, 0, 500); // PIEZO 0으로 만듦
    digitalWrite(LED, LOW); // LED 끔
    digitalWrite(PIEZO, LOW); // PIEZO 끔
   }
}

