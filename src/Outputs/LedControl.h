#ifndef LedControl_h 
#define LedControl_h 

#include <stdint.h>
#include <Arduino.h>

namespace LedColor{
    const uint8_t WHITE[3] = {255,255,255};
    const uint8_t RED[3]   = {255,0,0};
    const uint8_t GREEN[3] = {0,255,0};
    const uint8_t BLUE[3]  = {0,0,255};
}

// TODO: Add LED and RGB LED classes

/* RGD LED Functions */

void run_led(const uint8_t pins[3], const uint8_t color[3] = LedColor::WHITE){
    run_led(pins, nullptr, 0, color);
}

void run_led(const uint8_t pins[3], unsigned long* series, size_t len, const uint8_t color[3] = nullptr){
    //TODO: Add a sequence based LED control for status
}


/* Regular LED Functions */

void run_led(uint8_t pin){
    run_led(pin, nullptr, 0);
}

void run_led(uint8_t pin, const unsigned long* series, size_t len){
    //TODO: Add a sequence based LED control for status
}

#endif