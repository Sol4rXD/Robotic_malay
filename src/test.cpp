#include <Arduino.h>
#include <techkit.h>

void setup() {
  Serial.begin(9600);
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){8, 10}, SensorCount);
}

void loop() {
  // Debugging
  check_fi9Ueld();
  
  Serial.print("Sensor 1: ");
  Serial.print(LIGHT_1);
  Serial.print("\tSensor 2: ");
  Serial.println(LIGHT_2);

  delay(250);
}
