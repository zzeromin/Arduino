// PWM으로 모터 속도 제어

int ENA = 10;
int IN1 = 9; //
int IN2 = 8; //
int IN3 = 7; //
int IN4 = 6; //
int ENB = 5; //

void  setup()  {
  pinMode(ENA, OUTPUT); //
  pinMode(ENB, OUTPUT); //
  pinMode(IN1, OUTPUT); //
  pinMode(IN2, OUTPUT); //
  pinMode(IN3, OUTPUT); //
  pinMode(IN4, OUTPUT); //
}

void  loop()
{
  motor_control(255, 1, 0, 1, 0); // foward
  delay(2000);
  motor_control(64, 0, 1, 0, 1); // back
  delay(2000);
  motor_control(127, 1, 0, 0, 0); // right
  delay(2000);
  motor_control(127, 0, 0, 1, 0); // left
  delay(2000);
}

void motor_control(int mSpeed, int v1, int v2, int v3, int v4)
{
  analogWrite(ENA, mSpeed); // motor speed(0~255)
  digitalWrite(IN1, v1);
  digitalWrite(IN2, v2);
  digitalWrite(IN3, v3);
  digitalWrite(IN4, v4);
}
