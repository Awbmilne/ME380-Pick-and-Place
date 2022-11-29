#ifndef Auto_Cycle_h
#define Auto_Cycle_h

#include "../config.h"
#include "../Outputs/Outputs.h"
#include "ReturnHome.h"
#include "SystemState.h"
#include "AutoCycleState.h"

/**
 * @brief Commands for controllign the state of the Auto cycle
 * 
 */
enum class AutoCycleCommand{
    NONE,
    START,
    STOP,
    PAUSE,
    CONTINUE,
};


/**
 * @brief Using the current auto-cycle state, run the Auto-cycle
 * 
 * @arg cmd The AutoCycleCommand to pass to the auto-cycle state system.
 * @return bool Auto-Cycle was completed
 */
bool run_auto_cycle(AutoCycleCommand cmd = AutoCycleCommand::NONE){
    // Handle State Control Commands
    switch (cmd){
        case AutoCycleCommand::NONE:
            // Nothing
            break;

        case AutoCycleCommand::START:
            if (systemState == SystemState::STANDBY
             && autoCycleState == AutoCycleState::NONE
             && (returnHomeState == ReturnHomeState::HOME
             || returnHomeState == ReturnHomeState::NOT_HOME)){
                // Start the Auto Cycle
                run_return_home(ReturnHomeCommand::START);
                systemState = SystemState::AUTO_CYCLE;
                autoCycleState = AutoCycleState::START_HOME;
            }
            break;

        case AutoCycleCommand::STOP:
            systemState = SystemState::STANDBY; 
            autoCycleState = AutoCycleState::NONE;
            run_return_home(ReturnHomeCommand::STOP);
            GranularControl::stop_all();
            return false;

        case AutoCycleCommand::PAUSE:
            systemState = SystemState::CYCLE_PAUSE;
            run_return_home(ReturnHomeCommand::STOP);
            GranularControl::stop_all();
            return false;

        case AutoCycleCommand::CONTINUE:
            if (autoCycleState == AutoCycleState::NONE) break;
            else if (autoCycleState == AutoCycleState::START_HOME
             || autoCycleState == AutoCycleState::END_HOME)
                run_return_home(ReturnHomeCommand::START);
            else{
                // Go back 1 step and allow the system to restart the current step
                autoCycleState = static_cast<AutoCycleState>(static_cast<unsigned int>(autoCycleState) - 1);
            }
            systemState = SystemState::AUTO_CYCLE;
            break;
    }

    // Handle the internal state flow
    switch (autoCycleState){
        case AutoCycleState::NONE:
            // Nothing
            break;

        case AutoCycleState::START_HOME:
            if (returnHomeState == ReturnHomeState::NOT_HOME)
                return run_auto_cycle(AutoCycleCommand::STOP);
            else if (returnHomeState != ReturnHomeState::HOME)
                break;
            // Move to next step
            autoCycleState = AutoCycleState::MOVE_TO_A;
            Boom.set_angle(boomBinAPosition);
            // Intentional Non-break

        case AutoCycleState::MOVE_TO_A:
            if (Boom.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::LOWER_AT_A;
            Lifter.set_angle(Lifter.maxAngle);
            // Intentional Non-break

        case AutoCycleState::LOWER_AT_A:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::CLOSE_AT_A;
            Gripper.set_angle(Gripper.maxAngle);
            // Intentional Non-break

        case AutoCycleState::CLOSE_AT_A:
            if (Gripper.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::RAISE_AT_A;
            Lifter.set_angle(Lifter.minAngle);
            // Intentional Non-break

        case AutoCycleState::RAISE_AT_A:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::MOVE_TO_B;
            Boom.set_angle(boomBinBPosition);
            // Intentional Non-break

        case AutoCycleState::MOVE_TO_B:
            if (Boom.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::LOWER_AT_B;
            Lifter.set_angle(Lifter.maxAngle);
            // Intentional Non-break

        case AutoCycleState::LOWER_AT_B:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::OPEN_AT_B;
            Gripper.set_angle(Gripper.minAngle);
            // Intentional Non-break

        case AutoCycleState::OPEN_AT_B:
            if (Gripper.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::RAISE_AT_B;
            Lifter.set_angle(Lifter.minAngle);
            // Intentional Non-break

        case AutoCycleState::RAISE_AT_B:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::MOVE_TO_C;
            Boom.set_angle(boomBinCPosition);
            // Intentional Non-break

        case AutoCycleState::MOVE_TO_C:
            if (Boom.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::LOWER_AT_C;
            Lifter.set_angle(Lifter.maxAngle);
            // Intentional Non-break

        case AutoCycleState::LOWER_AT_C:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::CLOSE_AT_C;
            Gripper.set_angle(Gripper.maxAngle);
            // Intentional Non-break

        case AutoCycleState::CLOSE_AT_C:
            if (Gripper.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::RAISE_AT_C;
            Lifter.set_angle(Lifter.minAngle);
            // Intentional Non-break

        case AutoCycleState::RAISE_AT_C:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::MOVE_TO_D;
            Boom.set_angle(boomBinDPosition);
            // Intentional Non-break

        case AutoCycleState::MOVE_TO_D:
            if (Boom.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::LOWER_AT_D;
            Lifter.set_angle(Lifter.maxAngle);
            // Intentional Non-break

        case AutoCycleState::LOWER_AT_D:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::OPEN_AT_D;
            Gripper.set_angle(Gripper.minAngle);
            // Intentional Non-break

        case AutoCycleState::OPEN_AT_D:
            if (Gripper.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::RAISE_AT_D;
            Lifter.set_angle(Lifter.minAngle);
            // Intentional Non-break

        case AutoCycleState::RAISE_AT_D:
            if (Lifter.moving()) break;
            // Move to next step
            autoCycleState = AutoCycleState::END_HOME;
            run_return_home(ReturnHomeCommand::START);
            // Intentional Non-break

        case AutoCycleState::END_HOME:
            if (returnHomeState == ReturnHomeState::HOME)
                return true;
            if (returnHomeState == ReturnHomeState::NOT_HOME)
                return run_auto_cycle(AutoCycleCommand::STOP);
            break;
    }
    return false;
}

#endif