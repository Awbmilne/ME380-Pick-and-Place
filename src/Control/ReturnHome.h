#ifndef ReturnHome_h
#define ReturnHome_h

#include <stdint.h>
#include <Arduino.h>

#include "../Outputs/Outputs.h"
#include "SystemState.h"
#include "ReturnHomeState.h"

/**
 * @brief Return Home Command enumerator
 * 
 */
enum class ReturnHomeCommand{
    NONE,
    START,
    STOP
};


/**
 * @brief 
 * 
 * @param cmd ReturnHomeCommand to control the Return Home state system
 * @return bool System has returned to home
 */
bool run_return_home(ReturnHomeCommand cmd = ReturnHomeCommand::NONE){
    // Handle State control commands
    switch (cmd){
        case ReturnHomeCommand::NONE:
            // Nothing
            break;
        
        case ReturnHomeCommand::START:
            if (systemState == SystemState::STANDBY){
                // Start the Return Home sequence
                returnHomeState = ReturnHomeState::OPENING_GRIPPER;
                Gripper.set_angle(Gripper.maxAngle);
            }
            break;
        
        case ReturnHomeCommand::STOP:
            returnHomeState = ReturnHomeState::NOT_HOME;
            GranularControl::stop_all();
            return false;
    }

    // Handle internal state flow
    switch (returnHomeState){
        case ReturnHomeState::HOME:
        case ReturnHomeState::NOT_HOME:
            // Nothing to do
            break;
        
        case ReturnHomeState::OPENING_GRIPPER:
            if (Gripper.moving()) break;
            // Move to the next step
            returnHomeState = ReturnHomeState::RAISING_GRIPPER;
            Lifter.set_angle(Lifter.minAngle);
            // Intentional Non-break

        case ReturnHomeState::RAISING_GRIPPER:
            if (Lifter.moving()) break;
            // Move to the next step
            returnHomeState = ReturnHomeState::HOMEING_BOOM;
            Boom.home();
            // Intentional Non-break

        case ReturnHomeState::HOMEING_BOOM:
            if (Boom.moving()) break;
            // Move to the next step
            returnHomeState = ReturnHomeState::HOME;
            return true;
    }

    return false;
}

#endif