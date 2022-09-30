#ifndef Motors_h
#define Motors_h

#include <stdint.h>
#include <Arduino.h>

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

#endif