//  L298N 모터예제
int IN1 = 4; //
int IN2 = 5; //
int IN3 = 6; //
int IN4 = 7; //
//int ENA = 10;


void  setup()  {
//  채녈  A
pinMode(IN1, OUTPUT); //
pinMode(IN2, OUTPUT); //
pinMode(IN3, OUTPUT); //
pinMode(IN4, OUTPUT); //
//pinMode(ENA, OUTPUT); //
//pinMode(ENA, OUTPUT);
//digitalWrite(ENA, HIGH);
}

void  loop()
{
  //digitalWrite(ENA, HIGH);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(1000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(1000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(1000);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(1000);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  
  delay(1000);
}
