#ifndef Motors_h
#define Motors_h

#include <stdint.h>
#include <Arduino.h>
#include <AccelStepper.h>

#include "config.h"
#include "GranularServo.h"
#include "GranularStepper.h"

GranularServo Gripper(
    gripperServoPin,
    gripperDefaultAngle,
    gripperDefaultSpeed,
    gripperMinAngle,
    gripperMaxAngle,
    gripperMaxSpeed,
    gripperTravel,
    gripperGranularIncrementor,
    gripperServoMinPulse,
    gripperServoMaxPulse);

GranularServo Lifter(
    lifterServoPin,
    lifterDefaultAngle,
    lifterDefaultSpeed,
    lifterMinAngle,
    lifterMaxAngle,
    lifterMaxSpeed,
    lifterTravel,
    lifterGranularIncrementor,
    lifterServoMinPulse,
    lifterServoMaxPulse);

GranularStepper Boom(
    boomStepperType,
    boomStepperPins,
    boomHomeAngle,
    boomMaxAngle,
    boomMinAngle,
    boomStepsPerRev,
    boomDefaultSpeed,
    boomMaxSpeed,
    boomAcceleration,
    boomIncrementor,
    boomMinPulse);

#endif