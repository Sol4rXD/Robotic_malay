#include <Arduino.h>

// Use it to debugging
#define USE_DEBUG

#ifdef USE_DEBUG
#define DEBUG(str) Serial.println(str)
#else
#define DEBUG(str)
#endif

// Motor right
#define MOTOR_RIGHT_1 4
#define MOTOR_RIGHT_2 2 

// Motor left
#define MOTOR_LEFT_1 6
#define MOTOR_LEFT_2 8  

// Ultrasonic 
HardwareSerial &mySerial1 = Serial2;
HardwareSerial &mySerial2 = Serial1;

constexpr uint16_t TARGET_DISTANCE_THRESHOLD = 300; 
constexpr uint16_t FIELD_THRESHOLD = 1000; 
constexpr uint16_t SPEED_DEFAULT = 255; 

const String FORWARD = "FORWARD";
const String BACKWARD = "BACKWARD";

uint16_t distance_RIGHT, distance_LEFT;

bool targetDetected = false;

bool obstacleLeft;
bool obstacleRight;

// Light sensor
const uint8_t SensorCount = 2;
uint16_t sensorValues[SensorCount];

int LIGHT_SENSOR_1 = 8;
int LIGHT_SENSOR_2 = 9;

uint16_t LIGHT_1, LIGHT_2;