#ifndef Config_h
#define Config_h

#include <stdint.h>

/* Pin Configuration values */
const uint8_t gripperServoPin = 2; // Control pin for Gripper (MUST BE PWM!)
const uint8_t lifterServoPin =  3; // Control pin for Lifter (MUST BE PWM!)

/* Servo configuration parameters */
const float gripperDefaultAngle = 90; // Servo default position @ reset [deg]
const float gripperDefaultSpeed = 180; // Servo default speed @ reset [deg/sec]
const float gripperMinAngle = 0; // Software enforced angle limit [deg]
const float gripperMaxAngle = 180; // Software enforced angle limit [deg]
const float gripperMaxSpeed = 300; // Servo max rotational speed (dont exceed servo real speed ability) [deg/sec]
const float gripperTravel = 180; // Angle range for the specified pulse range [deg]
const uint32_t gripperServoMinPulse =  500; // Minimum pwm pulse width [μs]
const uint32_t gripperServoMaxPulse = 2500; // Maximum pwm pulse width [μs]

const float lifterDefaultAngle = 90; // Servo default position @ reset [deg]
const float lifterDefaultSpeed = 180; // Servo default speed @ reset [deg/sec]
const float lifterMinAngle = 0; // Software enforced angle limit [deg]
const float lifterMaxAngle = 180; // Software enforced angle limit [deg]
const float lifterMaxSpeed = 300; // Servo max rotational speed (dont exceed servo real speed ability) [deg/sec]
const float lifterTravel = 180; // Angle range for the specified pulse range [deg]
const uint32_t lifterServoMinPulse =  500; // Minimum pwm pulse width [μs]
const uint32_t lifterServoMaxPulse = 2500; // Minimum pwm pulse width [μs]

/* General config values */
const float granularIncrementor = 3; // Step size for serial controlled granular movement [deg]
const unsigned int refreshRate = 1000; // Frequency of updates for the servo positioning [hz]

/* Temporary timing measurement storage */
extern volatile uint32_t timeSum;
extern volatile uint32_t cycleCount;
extern volatile uint32_t minTime;
extern volatile uint32_t maxTime;

#endif 
