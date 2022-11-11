#ifndef CommandParsing_h
#define CommandParsing_h

#include <stdint.h>
#include <Arduino.h>

#include "../Outputs/Outputs.h"
#include "SystemState.h"
#include "ReturnHome.h"
#include "Calibration.h"
#include "AutoCycle.h"

/**
 * @brief Help message to be sent over Serial control terminal
 * 
 */
const char helpString[] = "============ List of Commands ============\n"
                          " h - Help menu (this menu)                \n"
                          " r - Reset motors to default position     \n"
                          " . - Start the calibration sequence       \n"
                         " \\ - Start the Auto-Cycle sequence        \n"
                          " ` - Pause the Auto-Cycle                 \n"
                          " ~ - Resume the Auto-Cycle                \n"
                          " [space] - Stop all motion and sequences  \n"
                          "                                          \n"
                          "---- Granular Control --------------------\n"
                          "               Gripper up                 \n"
                          "                    I                     \n"
                          " Gripper Close - J  K  L - Gripper Open   \n"
                          "              Gripper Down                \n"
                          "      Boom CCW - N     M - Boom CW        \n"
                          "                                          \n"
                          "---- Motion Control ----------------------\n"
                          "               Gripper up                 \n"
                          "                    W                     \n"
                          " Gripper Close - A  S  D - Gripper Open   \n"
                          "              Gripper Down                \n"
                          "      Boom CCW - X     C - Boom CW        \n"
                          "==========================================\n";

// Send the help message to specified stream object
void sendHelpMessage(Stream& stream){
    stream.write(helpString);
}

/**
 * @brief Check if the system is in a state where movement commands are allowed.
 * 
 * @param stream 
 * @return true 
 * @return false 
 */
bool move_check(Stream& stream, const char command = 0){
    if (systemState == SystemState::UNCALIBRATED && command != '.'){
        stream.println("System must be calibrated before this commands is allowed!");
        return false;
    }
    if (systemState != SystemState::STANDBY
     || returnHomeState != ReturnHomeState::HOME
     && returnHomeState != ReturnHomeState::NOT_HOME){
        stream.println("This command cannot be called during movement sequence!");
        return false;
     }
     return true;
}

/**
 * @brief Parse commands from the specified stream and trigger necessary actions
 * 
 * @param stream 
 * @return int The number of character commands remaining
 */
int ParseCommands(Stream& stream){
    if (stream.available()){
        char command = stream.read();
        switch (command){
            // H pressed for 'help'
            case 'H': 
            case 'h':
                sendHelpMessage(stream);
                break;

            // Start the Calibration
            case '.':
                if (!move_check(stream, command)) break;
                run_calibration(CalibrationCommand::START);
                stream.println("Calibration sequence started.");
                break;
            // Start the Auto-Cycle
            case '\\':
                if (!move_check(stream)) break;
                run_auto_cycle(AutoCycleCommand::START);
                stream.println("Auto Cycle started.");
                break;
            // Stop the cycle, or Calibration
            case ' ':
                GranularControl::stop_all();
                run_return_home(ReturnHomeCommand::STOP);
                run_calibration(CalibrationCommand::STOP);
                run_auto_cycle(AutoCycleCommand::STOP);
                stream.println("All sequences stopped.");
                break;
            // Pause/Cancel the current action
            case '`':
                GranularControl::stop_all();
                run_calibration(CalibrationCommand::STOP);
                run_auto_cycle(AutoCycleCommand::PAUSE);
                stream.println("Motion stopped.");
                break;
            // Resume the Cycle
            case '~':
                if (systemState == SystemState::CYCLE_PAUSE){
                    run_auto_cycle(AutoCycleCommand::CONTINUE);
                    stream.println("Auto Cycle resumed.");
                }
                else stream.println("Nothing to resume");
                break;

            // Return to home, stops first
            case 'R':
            case 'r':
                if (!move_check(stream)) break;
                GranularControl::stop_all();
                run_calibration(CalibrationCommand::STOP);
                run_auto_cycle(AutoCycleCommand::STOP);
                run_return_home(ReturnHomeCommand::START);
                stream.println("Returning to home position");
                break;

            // Granular Control
            case 'I':
            case 'i':
                if (!move_check(stream)) break;
                Lifter--;
                break;
            case 'K':
            case 'k':
                if (!move_check(stream)) break;
                Lifter++;
                break;
            case 'J':
            case 'j':
                if (!move_check(stream)) break;
                Gripper++;
                break;
            case 'L':
            case 'l':
                if (!move_check(stream)) break;
                Gripper--;
                break;
            case 'N':
            case 'n':
                if (!move_check(stream)) break;
                Boom--;
                break;
            case 'M':
            case 'm':
                if (!move_check(stream)) break;
                Boom++;
                break;

            // Motion Control
            case 'W':
            case 'w':
                if (!move_check(stream)) break;
                Lifter.set_angle(Lifter.minAngle);
                break;
            case 'S':
            case 's':
                if (!move_check(stream)) break;
                Lifter.set_angle(Lifter.maxAngle);
                break;
            case 'A':
            case 'a':
                if (!move_check(stream)) break;
                Gripper.set_angle(Gripper.maxAngle);
                break;
            case 'D':
            case 'd':
                if (!move_check(stream)) break;
                Gripper.set_angle(Gripper.minAngle);
                break;

            case 'X':
            case 'x':
                if (!move_check(stream)) break;
                Boom.set_motion(GranularControl::CCW);
                break;

            case 'C':
            case 'c':
                if (!move_check(stream)) break;
                Boom.set_motion(GranularControl::CW);
                break;

            // Ignore other commands
            default:
                stream.print("Invalid command '");
                stream.print(command);
                stream.println("'");
                break;
        }
    }
    return stream.available();
}

#endif