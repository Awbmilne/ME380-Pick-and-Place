#ifndef Outputs_h
#define Outputs_h

#include "config.h"
#include "GranularServo.h"
#include "GranularStepper.h"

/**
 * @brief Gripper servo motor
 * 
 */
GranularServo Gripper(
    gripperServoPin,
    gripperEnablePin,
    gripperEnableState,
    gripperDefaultAngle,
    gripperDefaultSpeed,
    gripperMinAngle,
    gripperMaxAngle,
    gripperMaxSpeed,
    gripperTravel,
    gripperGranularIncrementor,
    gripperServoMinPulse,
    gripperServoMaxPulse);

/**
 * @brief Lifter servo motor
 * 
 */
GranularServo Lifter(
    lifterServoPin,
    lifterEnablePin,
    lifterEnableState,
    lifterDefaultAngle,
    lifterDefaultSpeed,
    lifterMinAngle,
    lifterMaxAngle,
    lifterMaxSpeed,
    lifterTravel,
    lifterGranularIncrementor,
    lifterServoMinPulse,
    lifterServoMaxPulse);

/**
 * @brief Boom stepper motor
 * 
 */
GranularStepper Boom(
    boomStepperType,
    boomStepperPins,
    boomHomeAngle,
    boomCalibrationAngle,
    boomMaxAngle,
    boomMinAngle,
    boomStepsPerRev,
    boomDefaultSpeed,
    boomMaxSpeed,
    boomAcceleration,
    boomIncrementor,
    boomMinPulse);

#endif