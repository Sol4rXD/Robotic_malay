#include <Arduino.h>
#include <techkit.h>

void setup() {
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);

  delay(3000);
}

void loop() {
  if (!targetDetected) {
    target_scan(); 
  } else {
    target_lock(); 
  }
}
