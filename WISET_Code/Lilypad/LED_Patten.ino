void setup() {
  // put your setup code here, to run once:
  int i;
  for(i=7; i<=11; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  sequential();
  twoledBlink();
  threeledBlink();
  fiveledBlink();
  fiveledBlink();
}
  
void sequential()
{
  int d;
  for(d=7; d<=11; d++) {
    digitalWrite(d, HIGH);
    delay(300);
  }
  delay(300);
  for(d=7; d<=11; d++) {
    digitalWrite(d, LOW);
    delay(300);
  }
  delay(500);
}

void twoledBlink()
{
  // 2 led on off
  int d;
  for(d=7; d<=8; d++) {
    digitalWrite(d, HIGH);
  }
  delay(500);
  for(d=7; d<=8; d++) {
    digitalWrite(d, LOW);
  }
  delay(500);
}
void threeledBlink()
{
  // 3 led on off
  int d;
  for(d=9; d<=11; d++) {
    digitalWrite(d, HIGH);
  }
  delay(500);
  for(d=9; d<=11; d++) {
    digitalWrite(d, LOW);
  }
  delay(500);
}

void fiveledBlink()
{
  // 5 led on off
  int d;
  for(d=7; d<=11; d++) {
    digitalWrite(d, HIGH);
  }
  delay(500);
  for(d=7; d<=11; d++) {
    digitalWrite(d, LOW);
  }
  delay(500);
}
