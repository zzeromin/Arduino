// 버튼 2개로 LED 켜고 끄기(Button_Two 예제)

int LED = 13;
int buttonA = 7;
int buttonB = 2;

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(buttonA, INPUT); 
  pinMode(buttonB, INPUT); 
}
 
void loop() 
{
 int val_A, val_B;
 
  val_A = digitalRead(buttonA);
  val_B = digitalRead(buttonB);
  
  if ( val_A == LOW || val_B == LOW )
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
}
