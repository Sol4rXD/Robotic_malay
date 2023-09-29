#include <Arduino.h>
#include <definations.h>

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void move_RIGHTmotor(int speed, int direction) {
  analogWrite(MOTOR_RIGHT_1, speed);
  digitalWrite(MOTOR_RIGHT_2, direction);
}

void move_LEFTmotor(int speed, int direction) {
  analogWrite(MOTOR_LEFT_1, speed);
  digitalWrite(MOTOR_LEFT_2, direction);
}

void measure_distance() {
    // LEFT
    pinMode(TRIQ_PIN_1, OUTPUT);
    digitalWrite(TRIQ_PIN_1, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIQ_PIN_1, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIQ_PIN_1, LOW);
    pinMode(TRIQ_PIN_1, INPUT);
    duration_1 = pulseIn(TRIQ_PIN_1, HIGH);
    distance_1 = microsecondsToCentimeters(duration_1); // CM Unit

    // RIGHT
    pinMode(TRIQ_PIN_2, OUTPUT);
    digitalWrite(TRIQ_PIN_2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIQ_PIN_2, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIQ_PIN_2, LOW);
    pinMode(TRIQ_PIN_2, INPUT);
    duration_2 = pulseIn(TRIQ_PIN_2, HIGH);
    distance_2 = microsecondsToCentimeters(duration_2); // CM Unit
}

void target_lock() {
  measure_distance();

  bool obstacleLeft = distance_1 < TARGET_DISTANCE_THRESHOLD;
  bool obstacleRight = distance_2 < TARGET_DISTANCE_THRESHOLD;

  if (obstacleLeft && !obstacleRight) {
    move_RIGHTmotor(SPEED_DEFAULT, FORWARD);
    move_LEFTmotor(SPEED_DEFAULT - 20, FORWARD);

  } else if (!obstacleLeft && obstacleRight) {
    move_RIGHTmotor(SPEED_DEFAULT - 20, FORWARD);
    move_LEFTmotor(SPEED_DEFAULT, FORWARD);

  } else {
    move_RIGHTmotor(SPEED_DEFAULT, FORWARD);
    move_LEFTmotor(SPEED_DEFAULT, FORWARD);
  }
}







