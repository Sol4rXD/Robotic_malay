#include <Arduino.h>
#include <techkit.h>

void setup() {
  Serial.begin(115200);
  
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);

  pinMode(LIGHT_SENSOR_PIN_1, INPUT);
  pinMode(LIGHT_SENSOR_PIN_2, INPUT);

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
