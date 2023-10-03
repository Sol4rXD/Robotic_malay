#include <Arduino.h>

unsigned long time;
int color = 0; // Initialize color as 0, indicating no border detected
int last = 0;
int last_color = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  delayMicroseconds(12);
  pinMode(9, INPUT);
  time = micros();
  while (digitalRead(9)) {}

  // Adjust this threshold value to match your sensor's behavior
  int threshold = 1000;

  // Check if a transition from white to black is detected based on the time elapsed
  if ((micros() - time) > threshold) {
    color = 1; // Detected the transition from white to black (border)
  } else {
    color = 0; // No transition detected (white field)
  }

  // Print the status of the border
  if (color != last_color) {
    if (color == 1) {
      Serial.println("Approaching the black border");
    } else {
      Serial.println("On the white field");
    }
  }

  last = micros() - time;
  last_color = color;
}
