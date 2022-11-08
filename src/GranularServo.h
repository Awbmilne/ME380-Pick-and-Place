#ifndef GranularServo_h
#define GranularServo_h

#include <stdlib.h>
#include <stdint.h>
#include <Arduino.h>

#ifndef ARDUINO_TEENSY40
    #include <time.h>
    #include <Servo.h>
#else 
    #include <TimeLib.h>
    #include <PWMServo.h>
#endif

#include "GranularControl.h"

/**
 * @brief Servo wrapper that provides rough speed control and controllable motion.
 * 
 */
class GranularServo: GranularControl{
    public:
        /**
         * @brief Construct a new Granular Servo object
         * 
         * @param servoPin The PWM pin for controlling the servo
         * @param maxSpeed The software limited speed of the
         * @param defaultAngle The default angle for the servo, used at startup
         * @param minAngle The software enforced min angle limit
         * @param maxAngle The software enforced max angle limit
         * @param travel The physical travel limit of the servo for the pulse range
         * @param minPulse Minimum PWM pulse length
         * @param maxPulse Maximum PWM pulse length
         */
        GranularServo(uint8_t servoPin,
                      float defaultAngle,
                      float defaultSpeed,
                      float minAngle,
                      float maxAngle,
                      float maxSpeed,
                      float travel,
                      float incrementor,
                      uint32_t minPulse,
                      uint32_t maxPulse):
            servoPin(servoPin),
            defaultAngle(defaultAngle),
            defaultSpeed(defaultSpeed),
            minAngle(minAngle),
            maxAngle(maxAngle),
            maxSpeed(maxSpeed),
            travel(travel),
            incrementor(incrementor),
            minPulse(minPulse),
            maxPulse(maxPulse){}

        void setup();
        float get_angle();
        void set_angle(float angle);
        void set_speed(float rate);
        void set_speedp(float percent);
        void set_motion(direction dir);
        void set_motion(direction dir, float rate);

        void operator++(int);
        void operator--(int);

        void run();
        void stop(){set_angle(get_angle());}
        void reset(){setup();}

        const uint8_t servoPin;
        const float defaultAngle;
        const float defaultSpeed;
        const float minAngle;
        const float maxAngle;
        const float maxSpeed;
        const float travel;
        const float incrementor;
        const uint32_t minPulse;
        const uint32_t maxPulse;

    protected:
        #ifdef ARDUINO_TEENSY40
            PWMServo servo;
        #else
            Servo servo;
        #endif
        float speed;
        float goal;
        float position;
        time_t time;
};

#endif