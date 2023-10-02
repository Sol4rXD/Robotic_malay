#include <Arduino.h>

#define MOTOR_RIGHT_1 12 // CHECK
#define MOTOR_RIGHT_2 13 // CHECK

#define MOTOR_LEFT_1 12  // CHECK
#define MOTOR_LEFT_2 12  // CHECK

#define MOTOR_RIGHT_PWM 14  // CHECK
#define MOTOR_LEFT_PWM 15   // CHECK

#define TRIQ_PIN_LEFT 13 // CHECK
#define ECHO_PIN_LEFT 13    // CHECK

#define TRIQ_PIN_RIGHT 13 // CHECK
#define ECHO_PIN_RIGHT 13 // CHECK

#define LIGHT_SENSOR_PIN A0 // CHECK

const int TARGET_DISTANCE_THRESHOLD = 20; // CHECK
const int FIELD_THRESHOLD = 500; // CHECK (just measure on field first)
const int SPEED_DEFAULT = 255; // CHECK

const String FORWARD = "FORWARD";
const String BACKWARD = "BACKWARD";

long duration_RIGHT, duration_LEFT, distance_RIGHT, distance_LEFT;

bool targetDetected = false;

bool obstacleLeft;
bool obstacleRight;

int opacity;