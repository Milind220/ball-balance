#include <Servo.h>
#include <Wire.h>

// Introduce servo object
Servo servo;

// MACRODEFINITIONS
#define TRIGPIN 4
#define ECHOPIN 2
#define SERVOPIN 9
#define POT A5 
// This potentiometer is used to set the 'set-point', the point to
// which the system tries to return the ball to.


// VARIABLE DEFINITIONS
long duration;
float distance;
float elapsed_time, time, timePrev; // For use in derivative component.
float dist_prev_error, dist_error;
float set_point = 21.0; // Mid point of the balance.
float servo_angle;
float time_diff;
float time1 = 0;
float point_change;
int counter = 1;
float total;

// PID CONSTANTS
const float kp = 5.3; 
const float ki = 0.07;
const float kd = 1800;
float P, I, D, PID_total;


// TEMPERATURE AND HUMIDITY
// Adjust these values each time for best results.
const float hum = 83.0; // 70%
const float temp = 25.0; // degrees celcius
const float sound_sp = ((331.4 + (0.606*temp) + (0.0124*hum))/10000); // from m/s to cm/ms


void setup() {

  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(SERVOPIN, OUTPUT); // dunno if you need this
  servo.attach(9); // to control servo with pin 9
  servo.write(90); // to make balance horizontal to start
  Serial.begin(9600);

}

void loop() {
  
  distance = get_distance(); // Read distance of ball from center (error)
  total += distance;
  
  // Calculate PID values based on average of 4 distance readings, to
  // reduce the jitter introduced in the system with consecutive 
  // readings.
  if (counter % 4 == 0) { 

    set_point = set_centre();
    
    time_diff = (millis() - time1);  // Used with derivative component.
    distance = (total/4);  // Get the average of the 4 values.
    time1 = millis();

    dist_error = set_point - distance;
    
    P = kp * dist_error; // P value
    
    D = kd * ((dist_error - dist_prev_error)/time_diff); // D value
    
    if (-3 < dist_error < 3) {  // I Value
    // It is only useful for small accumulated errors that are going
    // otherwise uncorrected, so it is only used in a small range.
      I = I + (ki * dist_error); 
      }
    else {
      I = 0; 
      }
  
    PID_total = P + I + D;
    servo_angle = map(PID_total, 150, -150, 0, 150); // Get values to feed to servo motor.
    
    // Controlling servo.
    servo.write(servo_angle + 15); // 15 degree offset based on motor orientation in my build.
    dist_prev_error = dist_error;
    total = 0; // Reset the average.
    }
  counter += 1;
}

/// FUNCTION DEFINITIONS
float get_distance() {
  digitalWrite(TRIGPIN, LOW); // just to make sure in the beginning
  delay(2);
  digitalWrite(TRIGPIN, HIGH); 
  delay(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);

  return ((duration/2) * sound_sp);
}

float set_centre() {
  int value = map(analogRead(POT), 0, 1023, -10, +10);
  return (21.0 + value);
}