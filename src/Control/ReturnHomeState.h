#ifndef ReturnHomeState_h
#define ReturnHomeState_h

/**
 * @brief Return Home sequence states
 * 
 */
enum class ReturnHomeState{
    HOME,
    NOT_HOME,
    OPENING_GRIPPER,
    RAISING_GRIPPER,
    HOMEING_BOOM
};

/**
 * @brief Global variable for storing state of Return Home sequence
 * 
 */
ReturnHomeState returnHomeState = ReturnHomeState::NOT_HOME;

#endif
