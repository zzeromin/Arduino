// 출처 : an project done by Glen p yeldho
//      for more info and updates  https://www.facebook.com/glenp.yeldho
// 수정 : www.kocoafab.cc
// 수정 : zzeromin 2015-07-09
// 알파벳마다의 표기방법을 미리 설정합니다.
int _[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int A[] = {0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1};
int B[] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
int C[] = {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1};
int D[] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0};
int E[] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
int F[] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0};
int G[] = {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0};
int H[] = {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1};
int I[] = {0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1};
int J[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1};
int K[] = {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1};
int L[] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
int M[] = {1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
int N[] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1};
int O[] = {0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0};
int P[] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0};
int Q[] = {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1};
int R[] = {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1};
int S[] = {0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0};
int T[] = {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
int U[] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
int V[] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0};
int W[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0};
int X[] = {1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1};
int Y[] = {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1};
int Z[] = {1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1};
int letterSpace;
int dotTime;
int BUTTON = 3; // 푸쉬버튼 핀 번호
int val = 0; // 버튼 상태를 저장하는 변수
int val_OLD = 0;
int STATE = 0;

void setup()
{
  pinMode(BUTTON, INPUT_PULLUP); // LED을 출력으로 설정
  // 7-11번핀의 LED를 출력으로 설정합니다.
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // 글자 사이에 공간을 생성합니다.(단위:ms)
  letterSpace = 6;
  // 각 도트(LED)가 나타날 시간을 설정합니다. (단위:ms)
  dotTime = 3;

}
void printLetter(int letter[])
{
  int y;

  // 첫번째 y열을 출력합니다.
  for (y = 0; y < 5; y++)
  {
    digitalWrite(y + 7, letter[y]);
  }
  delay(dotTime);

  // 2번째 y열을 출력합니다.
  for (y = 0; y < 5; y++)
  {
    digitalWrite(y + 7, letter[y + 5]);
  }
  delay(dotTime);

  //3번째 y열을 출력합니다.
  for (y = 0; y < 5; y++)
  {
    digitalWrite(y + 7, letter[y + 10]);
  }
  delay(dotTime);

  // 문자 사이의 공간을 출력합니다.
  for (y = 0; y < 5; y++)
  {
    digitalWrite(y + 7, 0);
  }
  delay(letterSpace);
}
void loop()
{
  // 버튼을 입력하면 입력 값을 buttonstate에 저장
  val = digitalRead(BUTTON);

  if ( (val == HIGH) && (val_OLD == LOW) ) {
    STATE = 1 - STATE;
    delay(10);
  }
  val_OLD = val;

  // 버튼을 눌렀을 때 버튼 상태가 HIGH면
  if (STATE == HIGH) {
    // LED ON
    printLetter(L);
    printLetter(O);
    printLetter(V);
    printLetter(E);
    printLetter(_);
    // 출력하기를 원하는 문자를 순차적으로 입력합니다. 언더바는 공백을 의미합니다.
  }
  else {
    // LED OFF
    for (int i = 7; i <= 11; i++) {
      digitalWrite(i, LOW);
    }
  }
}
