#ifndef LimitSwitch_h
#define LimitSwitch_h

#include <stdint.h>
#include <Arduino.h>

#include <Bounce2.h>

#include "config.h"
#include "Sensor.h"

/**
 * @brief Add debounce and collective control to simple limit switch
 * 
 */
class LimitSwitch: Sensor{
    public:
        LimitSwitch(int pin, int defaultState, uint8_t mode=INPUT_PULLUP, unsigned int interval=2):
            pin(pin),
            defaultState(defaultState),
            mode(mode),
            interval(interval){
            }

        bool pressed(){
            return _switch.read() != defaultState;
        }

    protected:
        /**
         * @brief Run the setup for the switch with debounce
         * 
         */
        void setup(){
            _switch.attach(pin, mode);
            _switch.interval(interval);
        }

        /**
         * @brief 
         * 
         */
        void run(){
            _switch.update();
        }

    private:
        Bounce _switch = Bounce();
        const int pin;
        const int defaultState;  
        const uint8_t mode;    
        const unsigned int interval;  
};

#endif