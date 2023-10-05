#include <Arduino.h>

unsigned long time;
int color=1,last,last_color;
void setup()
{
 Serial.begin(9600);
}
void loop() {
 pinMode(9,OUTPUT);
 digitalWrite(9,HIGH);
 delayMicroseconds(12);
 pinMode(9,INPUT);
 time=micros();
 while(digitalRead(9)) {}
// Serial.println(micros()-time);
  
  if((micros()-time)>last && color==1) color=-1;
      else if((micros()-time)<last && color==-1) color=1;
   
    if(color!=last_color) Serial.print(color),Serial.println(" ");
    last=micros()-time;
    last_color=color;
}