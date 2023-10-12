#include <Arduino.h>
#include <definations.h>
#include <QTRSensors.h>

QTRSensors qtr;

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

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
  stop_allmotor(250);
  move_RIGHTmotor(255, BACKWARD);
  move_LEFTmotor(255, BACKWARD);
  delay(500); 
  move_RIGHTmotor(255, FORWARD);
  move_LEFTmotor(255, BACKWARD);
  delay(250);
  stop_allmotor(50);
}

void measure_distance() {
  // Sensor 1
  mySerial1.flush();
  mySerial1.write(0x55); 
  delay(100);
  HighByte1 = mySerial1.read();
  LowByte1 = mySerial1.read();
  Len1 = HighByte1 * 256 + LowByte1; 
  distance_LEFT = Len1;

  // Sensor 2
  mySerial2.flush();
  mySerial2.write(0x55); 
  delay(100);
  HighByte2 = mySerial2.read();
  LowByte2 = mySerial2.read();
  Len2 = HighByte2 * 256 + LowByte2; 
  distance_RIGHT = Len2;

  obstacleLeft = distance_LEFT < TARGET_DISTANCE_THRESHOLD;
  obstacleRight = distance_RIGHT < TARGET_DISTANCE_THRESHOLD;
}

void check_field() {
  qtr.read(sensorValues);

  LIGHT_1 = sensorValues[1];
  LIGHT_2 = sensorValues[0];

  if(LIGHT_1 < FIELD_THRESHOLD || LIGHT_2 < FIELD_THRESHOLD) {
    Serial.println("Make Uturn");
    make_uturn();
  }
}

void target_scan() {
  measure_distance();

  if (obstacleLeft || obstacleRight) {
    targetDetected = true;
    Serial.println("targetdetected = TRUE");
  } else {
    move_RIGHTmotor(255, FORWARD);
    move_LEFTmotor(255, BACKWARD);
  }
}

void target_lock() {
  measure_distance();

  if (obstacleLeft && !obstacleRight) {
    move_RIGHTmotor(SPEED_DEFAULT, FORWARD);
    stop_motorLEFT();

    targetDetected = true;
    Serial.println("targetdetected = TRUE");

  } else if (!obstacleLeft && obstacleRight) {
    stop_motorRIGHT();
    move_LEFTmotor(SPEED_DEFAULT, FORWARD);

    targetDetected = true;
    Serial.println("targetdetected = TRUE");

  } else if (obstacleLeft && obstacleRight) { 
    move_RIGHTmotor(SPEED_DEFAULT, FORWARD);
    move_LEFTmotor(SPEED_DEFAULT, FORWARD);

    targetDetected = true;
    Serial.println("targetdetected = TRUE");

  } else if (!obstacleLeft && !obstacleRight) {
    targetDetected = false;
    Serial.println("targetdetected = FALSE");
  }
}

void debugging() {
  static int time = millis();

  if(millis() - time >= 1500) {
    Serial.print("Sensor 1: ");
    Serial.print(LIGHT_1);
    Serial.print("\tSensor 2: ");
    Serial.println(LIGHT_2);
    Serial.print("Ultra Left: ");
    Serial.print(distance_LEFT);
    Serial.print("\tUltra Right: ");
    Serial.println(distance_RIGHT);
    Serial.println(targetDetected);
    Serial.println("------------------------------------");
    time = millis();
  }
}
