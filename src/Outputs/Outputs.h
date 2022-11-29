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
    gripperName,
    gripperServoPin,
    gripperEnablePin,
    gripperEnableState,
    gripperInvert,
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
    lifterName,
    lifterServoPin,
    lifterEnablePin,
    lifterEnableState,
    lifterInvert,
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
    boomName,
    boomStepperType,
    boomStepperPins,
    boomInvert,
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