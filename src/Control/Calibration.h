#ifndef Calibration_h
#define Calibration_h

#include <stdint.h>
#include <Arduino.h>

#include "../Inputs/Inputs.h"
#include "../Outputs/Outputs.h"
#include "ReturnHome.h"
#include "ReturnHomeState.h"
#include "CalibrationState.h"

/**
 * @brief Calibration Command enumerator
 * 
 */
enum class CalibrationCommand{
    NONE,
    START,
    STOP
};

/**
 * @brief Using the current calibration state, run the calibration
 * 
 * @param cmd The CalibrationCommand to pass to the calibration state system.
 * @return bool Calibration was completed
 */
bool run_calibration(CalibrationCommand cmd = CalibrationCommand::NONE){
    // Handle State control commands
    switch (cmd){
        case CalibrationCommand::NONE:
            // Nothing
            break;

        case CalibrationCommand::START:
            if ((systemState == SystemState::UNCALIBRATED
                || systemState == SystemState::STANDBY)
                && calibState == CalibrationState::NONE
                && (returnHomeState == ReturnHomeState::HOME
                || returnHomeState == ReturnHomeState::NOT_HOME)){
                // Start the calibration sequence
                systemState = SystemState::CALIBRATING;
                calibState = CalibrationState::FAST_MOVE_TO_SWITCH;
                Boom.set_calibrate(360);
                Boom.set_motion(GranularControl::CCW, Boom.defaultSpeed/2);
            }
            break;

        case CalibrationCommand::STOP:
            calibState = CalibrationState::NONE;
            systemState = SystemState::UNCALIBRATED;
            GranularControl::stop_all();
            return false;
    }
     
    // Proceed with calibration
    switch (calibState){
        case CalibrationState::NONE:
            //Nothing
            break;

        case CalibrationState::FAST_MOVE_TO_SWITCH:
            // Wait for the stepper to hit the switch
            if (BoomSwitch.pressed()){
                Boom.set_angle(Boom.get_angle() + 10);
                calibState = CalibrationState::BACK_OFF_SWITCH;
            }
            break;

        case CalibrationState::BACK_OFF_SWITCH:
            // Wait for the stepper to finish moving back from the switch
            if (!Boom.moving()){
                Boom.set_motion(GranularControl::CCW, Boom.defaultSpeed/2);
                calibState = CalibrationState::SLOW_MOVE_TO_SWITCH;
            }
            break;

        case CalibrationState::SLOW_MOVE_TO_SWITCH:
            // Wait for the stepper to trigger the switch
            if (BoomSwitch.pressed()){
                Boom.set_calibrate();
                calibState = CalibrationState::NONE;
                systemState = SystemState::STANDBY;
                run_return_home(ReturnHomeCommand::START);
                return true;
            }
            break;
    }

    // Calibration not complete
    return false;
    
}

#endif
