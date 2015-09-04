// 응용실습 스펙트럼 효과 만들기

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
}

void loop() {
  int i;
  for(i=1; i<=255; i++){
    analogWrite(redPin, i);
    delay(10);
    analogWrite(bluePin, 255-i);
    delay(10);
  }
   for(i=1; i<=255; i++){
    analogWrite(greenPin, i);
    delay(10);
    analogWrite(redPin, 255-i);
    delay(10);
  }
  for(i=1; i<=255; i++){
    analogWrite(bluePin, i);
    delay(10);
    analogWrite(greenPin, 255-i);
    delay(10);
  }  
}
