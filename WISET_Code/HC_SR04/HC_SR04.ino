/*Ultrasonic ranging module HC - SR04 provides 2cm - 400cm non-contact
measurement function, the ranging accuracy can reach to 3mm.
*/

int trigPin = 9;
int echoPin = 8;
int LED = 13;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello!");

  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  long duration, distance;

  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(3); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29; // The speed of sound is 340 m/s or 29 microseconds per centimeter.

  Serial.print(distance);
  Serial.print("cm");
  Serial.println();

  delay(200);
}
