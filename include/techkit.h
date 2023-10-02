#include <Arduino.h>
#include <definations.h>

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void move_RIGHTmotor(int speed, String direction) {
  analogWrite(MOTOR_RIGHT_PWM, speed); // PWM
  if(direction == "FORWARD"){ 
    digitalWrite(MOTOR_RIGHT_1, HIGH);
    digitalWrite(MOTOR_RIGHT_2, LOW);
  }
  else{
    digitalWrite(MOTOR_RIGHT_1, LOW);
    digitalWrite(MOTOR_RIGHT_2, HIGH);
  }
}

void move_LEFTmotor(int speed, String direction) {
  analogWrite(MOTOR_LEFT_PWM, speed); // PWM
  if(direction == "FORWARD"){
    digitalWrite(MOTOR_LEFT_1, HIGH);
    digitalWrite(MOTOR_LEFT_2, LOW);
  }
  else{
    digitalWrite(MOTOR_LEFT_1, LOW);
    digitalWrite(MOTOR_LEFT_2, HIGH); 
  }
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
    move_RIGHTmotor(SPEED_DEFAULT);
    move_LEFTmotor(SPEED_DEFAULT - 55);

  } else if (!obstacleLeft && obstacleRight) {
    move_RIGHTmotor(SPEED_DEFAULT - 55);
    move_LEFTmotor(SPEED_DEFAULT);

  } else {
    move_RIGHTmotor(SPEED_DEFAULT);
    move_LEFTmotor(SPEED_DEFAULT);
  }
}

void target_scan() {

}






