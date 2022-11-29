#ifndef GranularServo_h
#define GranularServo_h

// #include <stdlib.h>
#include <stdint.h>
// #include <Arduino.h>

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
         * @param name The name of the servo
         * @param servoPin The PWM pin for controlling the servo
         * @param enablePin The control pin for power supply to the servo
         * @param maxSpeed The software limited speed of the
         * @param defaultAngle The default angle for the servo, used at startup
         * @param minAngle The software enforced min angle limit
         * @param maxAngle The software enforced max angle limit
         * @param travel The physical travel limit of the servo for the pulse range
         * @param minPulse Minimum PWM pulse length
         * @param maxPulse Maximum PWM pulse length
         */
        GranularServo(const char* name,
                      uint8_t servoPin,
                      uint8_t enablePin,
                      bool enableState,
                      bool invert,
                      float defaultAngle,
                      float defaultSpeed,
                      float minAngle,
                      float maxAngle,
                      float maxSpeed,
                      float travel,
                      float incrementor,
                      uint32_t minPulse,
                      uint32_t maxPulse):
            name(name),
            minAngle(minAngle),
            maxAngle(maxAngle),
            servoPin(servoPin),
            enablePin(enablePin),
            enableState(enableState),
            invert(invert),
            defaultAngle(defaultAngle),
            defaultSpeed(defaultSpeed),
            maxSpeed(maxSpeed),
            travel(travel),
            incrementor(incrementor),
            minPulse(minPulse),
            maxPulse(maxPulse){
            pinMode(enablePin, OUTPUT); // Set the Mosfet as an Output
            digitalWrite(enablePin, enableState == LOW ? HIGH : LOW); // Disable the servo
        }

        float get_angle();
        bool moving();
        void set_angle(float angle, bool bypass_speed=false);
        void set_speed(float rate);
        void set_speedp(float percent);
        void set_motion(direction dir);
        void set_motion(direction dir, float rate);

        void operator++(int);
        void operator--(int);

        const char* name;
        const float minAngle;
        const float maxAngle;

    protected:
        void setup();
        void run();
        void run(bool force_update);
        void stop(){set_angle(get_angle());}
        void reset(){setup();}
        void output(Stream& stream);
    
        const uint8_t servoPin;
        const uint8_t enablePin;
        const bool enableState;
        const bool invert;
        const float defaultAngle;
        const float defaultSpeed;
        const float maxSpeed;
        const float travel;
        const float incrementor;
        const uint32_t minPulse;
        const uint32_t maxPulse;

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