#ifndef Config_h
#define Config_h

#include <stdint.h>

/* Pin Configuration values */
const uint8_t gripperServoPin = 2; // Control pin for Gripper (MUST BE PWM!)
const uint8_t lifterServoPin =  3; // Control pin for Lifter (MUST BE PWM!)

/* Servo configuration parameters */
const float gripperDefaultAngle = 90; // Servo default position @ reset [deg]
const float gripperDefaultSpeed = 25; // Servo default speed @ reset [deg/sec]
const float gripperMinAngle = 0; // Software enforced angle limit [deg]
const float gripperMaxAngle = 0; // Software enforced angle limit [deg]
const float gripperMaxSpeed = 45; // Servo max rotational speed (dont exceed servo real speed ability) [deg/sec]
const float gripperTravel = 180; // Angle range for the specified pulse range [deg]
const uint32_t gripperServoMinPulse =  500; // Minimum pwm pulse width [μs]
const uint32_t gripperServoMaxPulse = 2500; // Maximum pwm pulse width [μs]

const float lifterDefaultAngle = 90; // Servo default position @ reset [deg]
const float lifterDefaultSpeed = 25; // Servo default speed @ reset [deg/sec]
const float lifterMinAngle = 0; // Software enforced angle limit [deg]
const float lifterMaxAngle = 0; // Software enforced angle limit [deg]
const float lifterMaxSpeed = 45; // Servo max rotational speed (dont exceed servo real speed ability) [deg/sec]
const float lifterTravel = 180; // Angle range for the specified pulse range [deg]
const uint32_t lifterServoMinPulse =  500; // Minimum pwm pulse width [μs]
const uint32_t lifterServoMaxPulse = 2500; // Minimum pwm pulse width [μs]

#endif 
