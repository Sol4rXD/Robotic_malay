#include <Arduino.h>
#include <definations.h>
#include <QTRSensors.h>

QTRSensors qtr;

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
  // Sensor 1
  mySerial1.flush();
  mySerial1.write(0x55); 
  delay(100);
  if (mySerial1.available() >= 2) {
    HighByte1 = mySerial1.read();
    LowByte1 = mySerial1.read();
    Len1 = HighByte1 * 256 + LowByte1; 
    distance_LEFT = Len1;
  }

  // Sensor 2
  mySerial2.flush();
  mySerial2.write(0x55); 
  delay(100);
  if (mySerial2.available() >= 2) {
    HighByte2 = mySerial2.read();
    LowByte2 = mySerial2.read();
    Len2 = HighByte2 * 256 + LowByte2; 
    distance_RIGHT = Len2;
  }
  obstacleLeft = distance_LEFT < TARGET_DISTANCE_THRESHOLD;
  obstacleRight = distance_RIGHT < TARGET_DISTANCE_THRESHOLD;
}

void check_field() {
  qtr.read(sensorValues);

  LIGHT_1 = sensorValues[0];
  LIGHT_2 = sensorValues[1];

  if(LIGHT_1 || LIGHT_2 < FIELD_THRESHOLD) {
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


