#ifndef CalibrationState_h
#define CalibrationState_h

/**
 * @brief Calibration Cycle States
 * 
 */
enum class CalibrationState{
    NONE,
    FAST_MOVE_TO_SWITCH,
    BACK_OFF_SWITCH,
    SLOW_MOVE_TO_SWITCH
};

/**
 * @brief Global variable storing state of the Calibration cycle
 * 
 */
CalibrationState calibState = CalibrationState::NONE;

#endif
