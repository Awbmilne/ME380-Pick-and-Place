#ifndef AutoCycleState_h
#define AutoCycleState_h

/**
 * @brief Auto Cycle States
 * 
 */
enum class AutoCycleState{
    NONE       = 0,
    START_HOME = 1,
    MOVE_TO_A  = 2,
    LOWER_AT_A = 3,
    CLOSE_AT_A = 4,
    RAISE_AT_A = 5,
    MOVE_TO_B  = 6,
    LOWER_AT_B = 7,
    OPEN_AT_B  = 8,
    RAISE_AT_B = 9,
    MOVE_TO_C  = 10,
    LOWER_AT_C = 11,
    CLOSE_AT_C = 12,
    RAISE_AT_C = 13,
    MOVE_TO_D  = 14,
    LOWER_AT_D = 15,
    OPEN_AT_D  = 16,
    RAISE_AT_D = 17,
    END_HOME   = 18
};

/**
 * @brief Global variable storing state of the Auto Cycle
 * 
 */
AutoCycleState autoCycleState = AutoCycleState::NONE;

#endif
