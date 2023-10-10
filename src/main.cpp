#include <Arduino.h>
#include <techkit.h>

void setup() {
  Serial.begin(115200);
  
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);

  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){8, 10}, SensorCount);

  delay(3000);
}

void loop() {
  check_field();

  if (!targetDetected) {
    target_scan(); 
  } else {
    target_lock(); 
  }
}
