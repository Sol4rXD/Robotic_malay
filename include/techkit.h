#include <Arduino.h>
#include <definations.h>
#include <QTRSensors.h>
#include "smart_delay.h"

using vt::smart_delay;

QTRSensors qtr;

smart_delay sd1(100ul, millis);
smart_delay sd2(100ul, millis);
smart_delay sd3(1500, millis);

void move_RIGHTmotor(int speed, String direction) {
  if(direction == "FORWARD"){ 
    analogWrite(MOTOR_RIGHT_1, speed);
    digitalWrite(MOTOR_RIGHT_2, LOW);
  }
  else if(direction == "BACKWARD"){
    digitalWrite(MOTOR_RIGHT_1, LOW);
    analogWrite(MOTOR_RIGHT_2, speed);
  }
}

void move_LEFTmotor(int speed, String direction) {
  if(direction == "FORWARD"){
    analogWrite(MOTOR_LEFT_1, speed);
    digitalWrite(MOTOR_LEFT_2, LOW);
  }
  else if(direction == "BACKWARD"){
    digitalWrite(MOTOR_LEFT_1, LOW);
    analogWrite(MOTOR_LEFT_2, speed); 
  }
}

void stop_allmotor(int x) {
  digitalWrite(MOTOR_LEFT_1, HIGH);
  digitalWrite(MOTOR_LEFT_2, HIGH);
  digitalWrite(MOTOR_RIGHT_1, HIGH);
  digitalWrite(MOTOR_RIGHT_2, HIGH);
  delay(x);
} 

void stop_motorLEFT() {
  digitalWrite(MOTOR_LEFT_1, LOW);
  digitalWrite(MOTOR_LEFT_2, LOW);
}

void stop_motorRIGHT() {
  digitalWrite(MOTOR_RIGHT_1, LOW);
  digitalWrite(MOTOR_RIGHT_2, LOW);
}

void make_uturn() {
  if(LIGHT_RIGHT < FIELD_THRESHOLD) {
    move_RIGHTmotor(100, BACKWARD);
    move_LEFTmotor(255, BACKWARD);
    delay(750); 
    move_RIGHTmotor(RIGHT_SPEED, BACKWARD);
    move_LEFTmotor(LEFT_SPEED, FORWARD);
  }
  else {
    move_RIGHTmotor(100, BACKWARD);
    move_LEFTmotor(255, BACKWARD);
    delay(750); 
    move_RIGHTmotor(RIGHT_SPEED, FORWARD);
    move_LEFTmotor(LEFT_SPEED, BACKWARD);
  }
  delay(1000);
  stop_allmotor(50);
} 

void measure_distance() {
  // Sensor 1
  if (sd1) {
    mySerial1.flush();
    mySerial1.write(0x55); 
  }
  if (mySerial1.available() > 1) {
    distance_LEFT = 0;
    distance_LEFT |= static_cast<uint16_t>(mySerial1.read()) << 8;
    distance_LEFT |= static_cast<uint16_t>(mySerial1.read());
  }

  // Sensor 2
  if (sd2) {
    mySerial2.flush();
    mySerial2.write(0x55); 
  }
  if (mySerial2.available() > 1) {
    distance_RIGHT = 0;
    distance_RIGHT |= static_cast<uint16_t>(mySerial2.read()) << 8;
    distance_RIGHT |= static_cast<uint16_t>(mySerial2.read());
  }
  obstacleLeft = distance_LEFT < TARGET_DISTANCE_THRESHOLD;
  obstacleRight = distance_RIGHT < TARGET_DISTANCE_THRESHOLD;
}

void check_field() {
  qtr.read(sensorValues);

  LIGHT_RIGHT = sensorValues[1];
  LIGHT_LEFT = sensorValues[0];

  if(LIGHT_RIGHT < FIELD_THRESHOLD || LIGHT_LEFT < FIELD_THRESHOLD) {
    DEBUG("Make Uturn");
    make_uturn();
  }
}

void target_scan() {
  measure_distance();

  if (obstacleLeft || obstacleRight) {
    targetDetected = true;
    DEBUG("Enemies detected");
  } else {
    move_RIGHTmotor(RIGHT_SPEED, FORWARD);
    move_LEFTmotor(LEFT_SPEED, FORWARD);
  }
}
 
void target_lock() {
  measure_distance();

  if (obstacleLeft && !obstacleRight) {
    // stop_motorLEFT();
    move_LEFTmotor(LEFT_SPEED, BACKWARD);
    move_RIGHTmotor(RIGHT_SPEED, FORWARD);

    targetDetected = true;
    // DEBUG("targetdetected = TRUE");

  } else if (!obstacleLeft && obstacleRight) {
    // stop_motorRIGHT();
    move_RIGHTmotor(RIGHT_SPEED, BACKWARD);
    move_LEFTmotor(LEFT_SPEED, FORWARD);

    targetDetected = true;
    // DEBUG("targetdetected = TRUE");

  } else if (obstacleLeft && obstacleRight) { 
    move_RIGHTmotor(RIGHT_SPEED, FORWARD);
    move_LEFTmotor(LEFT_SPEED, FORWARD);

    targetDetected = true;
    // DEBUG("targetdetected = TRUE");

  } else if (!obstacleLeft && !obstacleRight) {
    targetDetected = false;
    // DEBUG("targetdetected = FALSE");
  }
}

void debugging() {
  if(sd3) {
    Serial.print("Sensor R: ");
    Serial.print(LIGHT_RIGHT);
    Serial.print("\tSensor L: ");
    Serial.println(LIGHT_LEFT);
    Serial.print("Ultra Left: ");
    Serial.print(distance_LEFT);
    Serial.print("\tUltra Right: ");
    Serial.println(distance_RIGHT);
    Serial.println(targetDetected);
    Serial.println("------------------------------------");
  }
}
