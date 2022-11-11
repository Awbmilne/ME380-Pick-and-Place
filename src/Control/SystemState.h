#ifndef SystemState_h
#define SystemState_h

/**
 * @brief System state values
 * 
 */
enum class SystemState{
    UNCALIBRATED,
    CALIBRATING,
    STANDBY,
    AUTO_CYCLE,
    CYCLE_PAUSE
};

/**
 * @brief Global variable for storing the System's state
 * 
 */
SystemState systemState = SystemState::UNCALIBRATED;

#endif