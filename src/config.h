#ifndef Config_h
#define Config_h

#include <stdint.h>
#include <AccelStepper.h>

/* Pin Configuration Values */
const uint8_t gripperServoPin = 2; // Control pin for Gripper (MUST BE PWM!)gripperMosfetPin,
const uint8_t gripperEnablePin = 3; // Servo power supply control pin
const int gripperEnableState = HIGH; // State for servo disable
const uint8_t lifterServoPin =  4; // Control pin for Lifter (MUST BE PWM!)
const uint8_t lifterEnablePin = 5; // Servo power supply control pin
const int lifterEnableState = HIGH; // State for servo disable
const uint8_t boomSwitchPin = 10; // Signal pin from the boom limit switch (DIGITAL PIN)

/* Servo Configuration Parameters */
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
const float lifterGranularIncrementor = 3; // Step size for serial controlled movement [deg]
const uint32_t lifterServoMinPulse =  500; // Minimum pwm pulse width [μs]
const uint32_t lifterServoMaxPulse = 2500; // Minimum pwm pulse width [μs]

/* Stepper Configuration Parameters */
const AccelStepper::MotorInterfaceType boomStepperType = AccelStepper::FULL4WIRE;
const uint8_t boomStepperPins[4] = {6,8,7,9}; // Pins used for stepper control
const float boomHomeAngle = 180; // Home angle for the boom to return to [deg]
const float boomMaxAngle = 350; // Max allowed angle for the boom [deg]
const float boomMinAngle = 10; // Min allowed angle for the boom [deg]
const float boomStepsPerRev = 200; // Number of steps per revolution [deg]
const float boomDefaultSpeed = 10; // Default speed of boom [deg/sec]
const float boomMaxSpeed = 15; // Max speed of boom [deg/sec]
const float boomAcceleration = 20; // Boom acceleration [deg/sec^2]
const float boomIncrementor = 2; // Step size for serial controlled movement [deg]
const uint32_t boomMinPulse = 20; // Minimum pwm pulse width [μs]
const float boomBinAPosition = 45;  // The anglular position of bin A
const float boomBinBPosition = 135; // The anglular position of bin B
const float boomBinCPosition = 225; // The anglular position of bin C
const float boomBinDPosition = 315; // The anglular position of bin D
const int boomSwitchDefaultState = LOW; // Default (unpressed) state of limit switch
const float boomCalibrationAngle = 11; // The calibrated location of the limit switch triggering [deg]

/* General Config Values */
const unsigned int refreshRate = 100; // Frequency of updates for the servo positioning [hz]
const unsigned int debounceInterval = 3; // Interval used to calculate debounce [ms]

#endif 
