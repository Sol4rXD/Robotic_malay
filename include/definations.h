#include <Arduino.h>

#define DEC 10

// Motor right
#define MOTOR_RIGHT_1 4 // CHECK
#define MOTOR_RIGHT_2 2 // CHECK

// Motor left
#define MOTOR_LEFT_1 8  // CHECK
#define MOTOR_LEFT_2 6  // CHECK

// Ultrasonic 
HardwareSerial &mySerial1 = Serial2;
HardwareSerial &mySerial2 = Serial1;


unsigned int HighByte1 = 0;
unsigned int LowByte1 = 0;
unsigned int Len1 = 0;

unsigned int HighByte2 = 0;
unsigned int LowByte2 = 0;
unsigned int Len2 = 0;

const int TARGET_DISTANCE_THRESHOLD = 50; // CHECK
const int FIELD_THRESHOLD = 1000; 
const int SPEED_DEFAULT = 255; // CHECK

const String FORWARD = "FORWARD";
const String BACKWARD = "BACKWARD";

long distance_RIGHT, distance_LEFT;

bool targetDetected = false;

bool obstacleLeft;
bool obstacleRight;

// Light sensor
const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];

int LIGHT_SENSOR_1 = 8;
int LIGHT_SENSOR_2 = 9;

int LIGHT_1, LIGHT_2;