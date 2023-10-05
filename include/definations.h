#include <Arduino.h>

#define DEC 10

// Motor right
#define MOTOR_RIGHT_1 12 // CHECK
#define MOTOR_RIGHT_2 13 // CHECK

// Motor left
#define MOTOR_LEFT_1 12  // CHECK
#define MOTOR_LEFT_2 12  // CHECK

// Motor both PWM
#define MOTOR_RIGHT_PWM A0  // CHECK
#define MOTOR_LEFT_PWM A1   // CHECK

// Ultrasonic 
HardwareSerial &mySerial1 = Serial1;
HardwareSerial &mySerial2 = Serial2;

unsigned int HighByte1 = 0;
unsigned int LowByte1 = 0;
unsigned int Len1 = 0;

unsigned int HighByte2 = 0;
unsigned int LowByte2 = 0;
unsigned int Len2 = 0;

const int TARGET_DISTANCE_THRESHOLD = 50; // CHECK
const int FIELD_THRESHOLD = 2500; 
const int SPEED_DEFAULT = 255; // CHECK

const String FORWARD = "FORWARD";
const String BACKWARD = "BACKWARD";

long duration_RIGHT, duration_LEFT, distance_RIGHT, distance_LEFT;

bool targetDetected = false;

bool obstacleLeft;
bool obstacleRight;

unsigned long time_1, time_2;

const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];

int LIGHT_1, LIGHT_2;