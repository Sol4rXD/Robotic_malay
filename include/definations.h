#include <Arduino.h>

#define MOTOR_RIGHT_1 12 
#define MOTOR_RIGHT_2 13 
#define MOTOR_RIGHT_PWM 14

#define MOTOR_LEFT_1 12  
#define MOTOR_LEFT_2 12  
#define MOTOR_LEFT_PWM 15

const int FORWARD = HIGH;
const int BACKWARD = LOW;

#define TRIQ_PIN_1 13 
#define ECHO_PIN_1 13

#define TRIQ_PIN_2 13 
#define ECHO_PIN_2 13

const int TARGET_DISTANCE_THRESHOLD = 20;
const int SPEED_DEFAULT = 150;

long duration_1, duration_2, distance_1, distance_2;

















