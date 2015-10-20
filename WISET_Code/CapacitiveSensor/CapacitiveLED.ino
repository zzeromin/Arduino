// CapacitiveSensor library link http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense

#include <CapacitiveSensor.h>

CapacitiveSensor sensor = CapacitiveSensor(2, 3);

int th = 120;
int LED = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
  // turn off autocalibrate on channel 1 - just as an example
}

void loop()
{
  long sensorValue = sensor.capacitiveSensor(30);
  Serial.println(sensorValue);

  if (sensorValue > th)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  delay(10);
}
