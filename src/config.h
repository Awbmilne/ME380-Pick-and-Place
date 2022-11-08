#ifndef Config_h
#define Config_h

#include <stdint.h>
#include <AccelStepper.h>

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
const float gripperGranularIncrementor = 3; // Step size for serial controlled granular movement [deg]
const uint32_t gripperServoMinPulse =  500; // Minimum pwm pulse width [μs]
const uint32_t gripperServoMaxPulse = 2500; // Maximum pwm pulse width [μs]

const float lifterDefaultAngle = 90; // Servo default position @ reset [deg]
const float lifterDefaultSpeed = 180; // Servo default speed @ reset [deg/sec]
const float lifterMinAngle = 0; // Software enforced angle limit [deg]
const float lifterMaxAngle = 180; // Software enforced angle limit [deg]
const float lifterMaxSpeed = 300; // Servo max rotational speed (dont exceed servo real speed ability) [deg/sec]
const float lifterTravel = 180; // Angle range for the specified pulse range [deg]
const float lifterGranularIncrementor = 3; // Step size for serial controlled granular movement [deg]
const uint32_t lifterServoMinPulse =  500; // Minimum pwm pulse width [μs]
const uint32_t lifterServoMaxPulse = 2500; // Minimum pwm pulse width [μs]

const AccelStepper::MotorInterfaceType boomStepperType = AccelStepper::FULL4WIRE;
const uint8_t boomStepperPins[4] = {5,7,6,8}; // Pins used for stepper control
const float boomHomeAngle = 180; // Home angle for the boom to return to [deg]
const float boomMaxAngle = 350; // Max allowed angle for the boom [deg]
const float boomMinAngle = 10; // Min allowed angle for the boom [deg]
const float boomStepsPerRev = 200; // Number of steps per revolution [deg]
const float boomDefaultSpeed = 10;
const float boomMaxSpeed = 15;
const float boomAcceleration = 20;
const float boomIncrementor = 2;
const uint32_t boomMinPulse = 20;

/* General config values */
const unsigned int refreshRate = 100; // Frequency of updates for the servo positioning [hz]

#endif 
