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


/**
 * @brief Servo wrapper that provides rough speed control and controllable motion.
 * 
 */
class GranularServo{
    // Class data structures
    public:
        enum direction{
            STOP = 0,
            CW = 1,
            CCW = 2,
        };
    // Methods
    public:
        GranularServo(uint8_t servoPin,
                      float defaultAngle,
                      float defaultSpeed,
                      float minAngle,
                      float maxAngle,
                      float maxSpeed,
                      float travel,
                      uint32_t minPulse,
                      uint32_t maxPulse);
        // Disable destructor for memory safety (shouldnt be needed)
        ~GranularServo();

        void setup();
        float get_angle();
        void set_angle(float angle);
        void set_speed(float rate);
        void set_speedp(float percent);
        void set_motion(direction dir);
        void set_motion(direction dir, float rate);

        void operator++(int);
        void operator--(int);

        void run(bool force = false);
        void reset(){setup();}
    
    // Static Methods
    public:
        static void run_all(bool force = false);

    // Public Members
    public:
        const uint8_t servoPin;
        const float defaultAngle;
        const float defaultSpeed;
        const float minAngle;
        const float maxAngle;
        const float maxSpeed;
        const float travel;
        const uint32_t minPulse;
        const uint32_t maxPulse;

    // Protected Members
    protected:
        #ifdef ARDUINO_TEENSY40
            PWMServo servo;
        #else
            Servo servo;
        #endif
        float speed;
        float goal;
        double position;
        time_t time;
        GranularServo* next = nullptr;

    // Static Members
    public:
        static GranularServo* first;
};

#endif
