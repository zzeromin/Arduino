// control led with HC-06(bluethooth module)
char val;
int ledpin = 13;

void setup()
{
  pinMode(ledpin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if ( Serial.available() )
  {
    val = Serial.read();
  }
  
  if ( val == 'H' )
    digitalWrite(ledpin, HIGH);
  else
    digitalWrite(ledpin, LOW);  

  delay(100);
}
