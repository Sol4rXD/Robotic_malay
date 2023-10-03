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
  else if(direction == "BACKWARD"){
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
  else if(direction == "BACKWARD"){
    digitalWrite(MOTOR_LEFT_1, LOW);
    digitalWrite(MOTOR_LEFT_2, HIGH); 
  }
}

void stop_allmotor(int x) {
  digitalWrite(MOTOR_LEFT_1, LOW);
  digitalWrite(MOTOR_LEFT_2, LOW);
  digitalWrite(MOTOR_RIGHT_1, LOW);
  digitalWrite(MOTOR_RIGHT_2, LOW);
  delay(x);
} 

void make_uturn() {
  stop_allmotor(1000);
  move_RIGHTmotor(255, BACKWARD);
  move_LEFTmotor(150, BACKWARD);
  stop_allmotor(500);
}

void measure_distance() {
    // LEFT
    pinMode(TRIQ_PIN_LEFT, OUTPUT);
    digitalWrite(TRIQ_PIN_LEFT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIQ_PIN_LEFT, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIQ_PIN_LEFT, LOW);
    pinMode(TRIQ_PIN_LEFT, INPUT);
    duration_LEFT = pulseIn(TRIQ_PIN_LEFT, HIGH);
    distance_LEFT = microsecondsToCentimeters(duration_LEFT); // CM Unit

    // RIGHT
    pinMode(TRIQ_PIN_RIGHT, OUTPUT);
    digitalWrite(TRIQ_PIN_RIGHT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIQ_PIN_RIGHT, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIQ_PIN_RIGHT, LOW);
    pinMode(TRIQ_PIN_RIGHT, INPUT);
    duration_RIGHT = pulseIn(TRIQ_PIN_RIGHT, HIGH);
    distance_RIGHT = microsecondsToCentimeters(duration_RIGHT); // CM Unit

    obstacleLeft = distance_LEFT < TARGET_DISTANCE_THRESHOLD;
    obstacleRight = distance_RIGHT < TARGET_DISTANCE_THRESHOLD;
}

void check_field() {
  digitalWrite(LIGHT_SENSOR_PIN_1, HIGH); 
  delayMicroseconds(10); 
  pinMode(LIGHT_SENSOR_PIN_1, INPUT);
  time_1 = micros();

  while (digitalRead(LIGHT_SENSOR_PIN_1) == HIGH) {}

  if ((micros() - time_1) > last_1 && color_1 == 1) {
    color_1 = -1;
  } else if ((micros() - time_1) < last_1 && color_1 == -1) {
    color_1 = 1;
  }

  // Sensor 2
  digitalWrite(LIGHT_SENSOR_PIN_2, HIGH); 
  delayMicroseconds(10); 
  pinMode(LIGHT_SENSOR_PIN_2, INPUT);
  time_2 = micros();

  while (digitalRead(LIGHT_SENSOR_PIN_2) == HIGH) {}

  if ((micros() - time_2) > last_2 && color_2 == 1) {
    color_2 = -1;
  } else if ((micros() - time_2) < last_2 && color_2 == -1) {
    color_2 = 1;
  }
  if (color_1 == -1 || color_2 == -1) {
    make_uturn();
  } 
}

void target_scan() {
  measure_distance();

  if (obstacleLeft || obstacleRight) {
    targetDetected = true;
  } else {
    move_RIGHTmotor(200, FORWARD);
    move_LEFTmotor(200, BACKWARD);
  }
}

void target_lock() {
  measure_distance();

  if (obstacleLeft && !obstacleRight) {
    move_RIGHTmotor(SPEED_DEFAULT, FORWARD);
    move_LEFTmotor(SPEED_DEFAULT - 55, FORWARD);

    targetDetected = true;

  } else if (!obstacleLeft && obstacleRight) {
    move_RIGHTmotor(SPEED_DEFAULT - 55, FORWARD);
    move_LEFTmotor(SPEED_DEFAULT, FORWARD);

    targetDetected = true;

  } else if (obstacleLeft && obstacleRight) { 
    move_RIGHTmotor(SPEED_DEFAULT, FORWARD);
    move_LEFTmotor(SPEED_DEFAULT, FORWARD);

    targetDetected = true;

  } else if (!obstacleLeft && !obstacleRight) {
    targetDetected = false;
  }
}


