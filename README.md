# PID Algorithm Ball Balance

This is a project that I made to better understand and apply the concept of PID control algorithms. The basic idea of this project is that a ball or a toy car is placed on the see-saw part of the balance, which actively tries to keep the object in the center. If the ball/toy car is externally disturbed, the balance/see-saw tilts in the opposite direction to negate the movement of the object.

In my project, the control algorithm I used was a simple PID (proportional-integral-derivative) control.

## How it works

An ultrasonic distance sensor (HC-SR04) mounted on one end of the see-saw measures the error (the distance between the set point, and the position of the object). It does this ~ 50 times/second, and feeds these readings into an Arduino Uno mounted on the base. The loop function in the Arduino contains the PID algorithm. With every run through the loop, it generates a total 'feedback value' based on the P, I and D gain values set. This is then mapped to a range of values which in turn control a servo motor (MG-996R) attached to the see-saw/balance. 
This completes the closed loop control system.

##  Gain Values

I set the gain values through trial and error. To begin with, I set the I and D gain values to 0, and tuned the P value until the balance returned the ball/toy car to the set point with only slight oscillation.

I then zeroed the P value as well, and tuned the D gain in isolation until the balance was effectively able to negate the velocity of the moving car/ball. At this point, with some additional minor tuning, the P-D controller was already very effective at returning the object to the set point and stopping its motion there. 

For the I gain, I experimented with very small values and limited its max value to prevent oscillation. I also set a limitation that ensures that I gain is only considered when the object is within a very short distance of the set point.

P gain: 

I gain: 

D gain:

