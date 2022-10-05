#ifndef Motors_h
#define Motors_h

#include <stdint.h>
#include <Arduino.h>
#include <AccelStepper.h>

#include "config.h"
#include "GranularServo.h"

GranularServo Gripper(
    gripperServoPin,
    gripperDefaultAngle,
    gripperDefaultSpeed,
    gripperMinAngle,
    gripperMaxAngle,
    gripperMaxSpeed,
    gripperTravel,
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
    lifterServoMinPulse,
    lifterServoMaxPulse);

AccelStepper Stepper(AccelStepper::FULL4WIRE, 5,7,6,8);


#endif