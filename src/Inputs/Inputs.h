#ifndef Inputs_h
#define Inputs_h

#include "../config.h"
#include "LimitSwitch.h"

/**
 * @brief Limit switch on Boom for angular calibration
 * 
 */
LimitSwitch BoomSwitch(
    boomSwitchPin,
    boomSwitchDefaultState,
    boomSwitchMode,
    debounceInterval
);

#endif