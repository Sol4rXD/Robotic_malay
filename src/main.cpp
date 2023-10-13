#include <Arduino.h>
#include <techkit.h>

constexpr const uint8_t QTR_PINS[] = {3, 7};

void setup() {
  Serial.begin(9600);
  mySerial1.begin(9600);
  mySerial2.begin(9600);
  
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);

  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);

  qtr.setTypeRC();
  qtr.setSensorPins(QTR_PINS, SensorCount);

  delay(3000);
}

void loop() {
  check_field();

  // Use it to debugging
  debugging();

  if (!targetDetected) {
    target_scan(); 
  } else {
    target_lock(); 
  }
}
