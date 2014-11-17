// sound sensor car
int out = 3;
int in = A0;
void setup()
{
  //Serial.begin(9600);
}

void loop()
{
  int controlA = analogRead(in);
//  Serial.print( "A = " );
//  Serial.println( controlA );
  
  if ( controlA > 100 )
     analogWrite( out, controlA );
  else
     analogWrite( out, 0 );
  delay(200);  
}
