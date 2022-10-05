#ifndef Motors_h
#define Motors_h

#include <stdint.h>
#include <Arduino.h>
#include <AccelStepper.h>

#include "config.h"
#include "GranularServo.h"

Servo Gripper;
Servo Lifter;

AccelStepper Stepper(AccelStepper::FULL4WIRE, 5,7,6,8);


#endif