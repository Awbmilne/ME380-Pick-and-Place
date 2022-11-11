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
                      float calibrationAngle,
                      float maxAngle,
                      float minAngle,
                      float stepsPerRev,
                      float defaultSpeed,
                      float maxSpeed,
                      float acceleration,
                      float incrementor,
                      uint32_t minPulse):
            homeAngle(homeAngle),
            calibrationAngle(calibrationAngle),
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
            _stepper.setMaxSpeed(defaultSpeed);
            _stepper.setAcceleration(acceleration);
            _stepper.setMinPulseWidth(minPulse);
        }

        void home();
        bool moving();
        float get_angle();
        void set_angle(float angle);
        void set_angle(float angle, float rate);
        void set_anglep(float angle, float percent);
        void set_speed(float rate);
        void set_speedp(float percent);
        void set_motion(direction dir);
        void set_motion(direction dir, float rate);
        void set_motionp(direction dir, float percent);
        void set_calibrate();

        void operator++(int);
        void operator--(int);

    protected:
        void setup();
        void run();
        void stop();
        void reset(){setup();}

        const float homeAngle;
        const float calibrationAngle;
        const float maxAngle;
        const float minAngle;
        const float stepsPerRev;
        const float defaultSpeed;
        const float maxSpeed;
        const float incrementor;
        
        AccelStepper _stepper;

        float step_to_angle(long step);
        long angle_to_step(float angle);
};

#endif