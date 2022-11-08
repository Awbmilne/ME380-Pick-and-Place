#ifndef GranularStepper_h
#define GranularStepper_h

#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>

#include <AccelStepper.h>

#include "GranularControl.h"

/**
 * @brief Servo wrapper that provides rough speed control and controllable motion.
 * 
 */
class GranularStepper: GranularControl{
    public:
        GranularStepper(AccelStepper::MotorInterfaceType type,
                      const uint8_t stepperPins[4],
                      float homeAngle,
                      float maxAngle,
                      float minAngle,
                      float stepsPerRev,
                      float defaultSpeed,
                      float maxSpeed,
                      float acceleration,
                      float incrementor,
                      uint32_t minPulse):
            homeAngle(homeAngle),
            maxAngle(maxAngle),
            minAngle(minAngle),
            stepsPerRev(stepsPerRev),
            defaultSpeed(defaultSpeed),
            maxSpeed(maxSpeed),
            incrementor(incrementor),
            _stepper(AccelStepper(type, 
                                 stepperPins[0],
                                 stepperPins[1],
                                 stepperPins[2],
                                 stepperPins[3])){
            _stepper.setAcceleration(acceleration);
            _stepper.setMinPulseWidth(minPulse);
        }

        void setup();
        void home();
        float get_angle();
        void set_angle(float angle);
        void set_angle(float angle, float rate);
        void set_anglep(float angle, float percent);
        void set_speed(float rate);
        void set_speedp(float percent);
        void set_motion(direction dir);
        void set_motion(direction dir, float rate);
        void set_motionp(direction dir, float percent);

        void operator++(int);
        void operator--(int);

        void run();
        void stop();
        void reset(){setup();}

        const float homeAngle;
        const float maxAngle;
        const float minAngle;
        const float stepsPerRev;
        const float defaultSpeed;
        const float maxSpeed;
        const float incrementor;

    protected:
        AccelStepper _stepper;

        float step_to_angle(long step);
        long angle_to_step(float angle);
};

#endif