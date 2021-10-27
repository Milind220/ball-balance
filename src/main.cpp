#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>

// MACRODEFINITIONS
#define TRIGPIN 6
#define ECHOPIN 7
#define SERVOPIN 9

// DECLARATIONS
Servo servo

// CONSTANT DEFINITIONS ///
const float temp = 27.0;
const float humidity = 70.0;
const float sound_speed = ((331.4 + (0.606*temp) + (0.0124*humidity))/10000);  in cm/ms


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(SERVOPIN);
  pinMode(TRIGPIN)

}

void loop() {
  // put your main code here, to run repeatedly:
}

/// FUNCTION DEFINITIONS ///
float get_distance(float sound_speed)  // sound speed in dist_unit/ms 
{
  // returns dist of car from sensor
  digitalWrite(TRIGPIN,LOW);
  delay(2);
  digitalWrite(TRIGPIN,HIGH);
  delay(10);
  digitalWrite(TRIGPIN,LOW);
  delay(2);

  long duration = pulseIn(ECHOPIN,HIGH);
  float distance = ((duration/2)*sound_speed) // distance in dist_unit of sound speed
  return(distance);
}

// one func to take in error, prev error, kp, kd, ki and calculate PID total gain
float PID_gain(float error, float prev_error, float kp, float ki, float kd, float I, float dt)
{
  float P,I,D;
  // P gain
  P = kp*error;
  // I gain, for most systems this is great
  if(-3<error<3)
    I+=ki*error;
  else
    I = 0;
  // D gain
  D = kd*((error-prev_error)/dt);
  // total gain
  float PID_total = P+I+D;
  
  return(PID_total);
}

