#include <Arduino.h>
#include <techkit.h>

void setup() {
  Serial.begin(9600);
  mySerial1.begin(9600);
  mySerial2.begin(9600);

  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){3, 7}, SensorCount);

  pinMode(MOTOR_RIGHT_1, OUTPUT);
  pinMode(MOTOR_RIGHT_2, OUTPUT);

  pinMode(MOTOR_LEFT_1, OUTPUT);
  pinMode(MOTOR_LEFT_2, OUTPUT);

  delay(3000);
}

void loop() {
  // Debugging  

  // Ultrasonic

  // measure_distance();
  // Serial.print("DistanceLEFT: ");
  // Serial.println(distance_LEFT);
  // Serial.print("DistanceRIGHT: ");
  // Serial.println(distance_RIGHT);
  // Serial.println("------------------------------------");

  // Light sensor 

  // check_field();
  // Serial.print("Sensor LEFT: ");
  // Serial.print(LIGHT_1);
  // Serial.print("\tSensor RIGHT: ");
  // Serial.println(LIGHT_2);
  // Serial.println("------------------------------------");
  // delay(250);

  // Motor

  move_LEFTmotor(255, FORWARD);
  move_RIGHTmotor(100, FORWARD);
  delay(3500);
  while (1)
  {
  }
  
  // Serial.println("MoTOR");
}



