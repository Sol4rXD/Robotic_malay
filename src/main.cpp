#include <Arduino.h>
#include <techkit.h>

void setup() {
  Serial.begin(9600);
  mySerial1.begin(9600);
  mySerial2.begin(9600);
  
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);

  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){3, 7}, SensorCount);

  delay(3000);
}

void loop() {
  check_field();

  // Enable for debug
  debugging();

  if (!targetDetected) {
    target_scan(); 
  } else {
    target_lock(); 
  }
}
