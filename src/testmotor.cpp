#include <Arduino.h>
#include <techkit.h>

void setup() {
  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);

  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);
}

void loop() {
  move_RIGHTmotor(255, FORWARD);
  move_LEFTmotor(255, FORWARD);
  delay(2000);
  move_RIGHTmotor(255, FORWARD);
  move_LEFTmotor(200, BACKWARD);
}
