#include <Arduino.h>

#define MOTOR_RIGHT_1 12 
#define MOTOR_RIGHT_2 13 

#define MOTOR_LEFT_1 12  
#define MOTOR_LEFT_2 12  

#define MOTOR_RIGHT_PWM 14
#define MOTOR_LEFT_PWM 15

#define TRIQ_PIN_LEFT 13 
#define ECHO_PIN_LEFT 13

#define TRIQ_PIN_RIGHT 13 
#define ECHO_PIN_RIGHT 13

const int TARGET_DISTANCE_THRESHOLD = 20;
const int SPEED_DEFAULT = 255;

const String FORWARD = "FORWARD";
const String BACKWARD = "BACKWARD";

long duration_RIGHT, duration_LEFT, distance_RIGHT, distance_LEFT;

bool targetDetected = false;

bool obstacleLeft;
bool obstacleRight;