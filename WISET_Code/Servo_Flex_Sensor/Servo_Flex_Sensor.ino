// Flex 센서를 이용해서 서보모터를 회전시키는 예제 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int flexpin = 0; // 센서값을 읽기 위해 0번을 flexpin에 지정

void setup() 
{ 
  Serial.begin(9600); // 시리얼 모니터 초기화
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
void loop() 
{ 
  int flexVal; // 센서값을 저장할 변수
  flexVal = analogRead(flexpin); //아날로그 입력 받음 (0~1023) 
  flexVal = map(flexVal, 0, 1023, 0, 120);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(flexVal);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there   
  
  Serial.print("sensor: "); // 시리얼 모니터에 ‘sensor: ’ 출력
  Serial.println(flexVal); // flexVal의 값을 출력, println은 줄바꿈
  delay(200);
} 

