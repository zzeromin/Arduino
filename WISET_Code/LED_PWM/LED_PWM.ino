// 03. 빛 조절 LED 스탠드 예제

int led = 9; // LED는 9번 핀을 사용
int i = 0;      // 증가, 감소를 위한 변수를 정의
 
void setup()
{
  pinMode(led, OUTPUT); // ledPin은 출력
}
 
void loop()
{
  for ( i = 0; i < 255; i++ ) {  // 0부터 254까지 반복
    analogWrite( led, i );    // led가 i크기만큼 밝아짐
    delay(10);    // 밝기 변화를 보기 위해 10ms 만큼 대기
  }

  for ( i = 255; i > 0; i-- ) {   // 255부터 1까지 반복
    analogWrite( led, i );    // led가 i크기만큼 어두워짐
    delay(10);   // 밝기 변화를 보기 위해 10ms 만큼 대기
  }
}
