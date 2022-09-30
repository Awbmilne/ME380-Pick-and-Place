#ifndef GranularServo_h
#define GranularServo_h

#include <stdint.h>
#include <Arduino.h>
#include <Servo.h>
#include <time.h>

enum direction{
    STOP = 0,
    CW = 1,
    CCW = 2,
};
/**
 * @brief Servo wrapper that provides rough speed control and controllable motion.
 * 
 */
class GranularServo{
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
                      uint32_t minPulse,
                      uint32_t maxPulse):
            servoPin(servoPin),
            defaultAngle(defaultAngle),
            defaultSpeed(defaultSpeed),
            minAngle(minAngle),
            maxAngle(maxAngle),
            maxSpeed(maxSpeed),
            travel(travel),
            minPulse(minPulse),
            maxPulse(maxPulse){}

        void setup();
        float get_angle();
        void set_angle(float angle);
        void set_speed(float rate);
        void set_speedp(float percent);
        void set_motion(direction dir);
        void set_motion(direction dir, float rate);

        void run();
        void reset(){setup();}

        const uint8_t servoPin;
        const float defaultAngle;
        const float defaultSpeed;
        const float minAngle;
        const float maxAngle;
        const float maxSpeed;
        const float travel;
        const uint32_t minPulse;
        const uint32_t maxPulse;

    protected:
        Servo servo;
        float speed;
        float goal;
        float position;
        time_t time;
};

#endif