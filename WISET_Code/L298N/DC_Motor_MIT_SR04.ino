// DC_Motor_MIT_SR04

#define IN1    4
#define IN2    5
#define IN3    6
#define IN4    7
#define LED    13

int trigPin = 9;
int echoPin = 8;

// IN1, IN2, IN3, IN4
void motor_control(int i1, int i2, int i3, int i4);

void setup()
{
    Serial.begin(9600);
    Serial.println("Hello!");

    for (int i = 4; i <= 7; i++) {
        pinMode(i, OUTPUT);
    }
    pinMode(LED, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10); // Added this line
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  //  자동차 앞 120cm 이내에 물체가 없으면 정지
  if ( distance > 120 || distance <= 0 ) {
    Serial.println("Out of range");
    motor_control(0, 0, 0, 0); // Stop
    digitalWrite(LED, LOW); 
  }
  //  10~100cm 내에 물체를 감지하면 출발
  else if ( distance > 10 && distance < 100 )
  {
    Serial.print("moving Forward! ");
    Serial.print(distance);
    Serial.println(" cm");
    
    motor_control(1, 0, 1, 0); // Forward
    digitalWrite(LED, HIGH);
    delay(100);
  }
  //  5cm 이내에 물체를 감지하면 후진
  else if ( distance <= 5 )
  {
    Serial.println("mvoing Back!");
    Serial.print(distance);
    Serial.println(" cm");
    
    motor_control(0, 1, 0, 1); // Back
    delay(500);
    blink_back();
    
    Serial.println("mvoing Left!");
    Serial.print(distance);
    Serial.println(" cm");
    motor_control(1, 0, 0, 0); // Left
    delay(800);
  }
}

void motor_control(int i1, int i2, int i3, int i4)
{
    //digitalWrite(ENA, a);
    digitalWrite(IN1, i1);
    digitalWrite(IN2, i2);
    ///digitalWrite(ENB, b);
    digitalWrite(IN3, i3);
    digitalWrite(IN4, i4);
}

void blink_back()
{
  digitalWrite(LED, HIGH);
  delay(20);
  digitalWrite(LED, LOW);
  delay(20);  
}
