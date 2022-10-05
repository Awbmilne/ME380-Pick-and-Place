#ifndef CommandParsing_h
#define CommandParsing_h

#include <stdint.h>
#include <Arduino.h>

#include "Motors.h"

const char helpString[] = "============ List of Commands ============\n"
                          " h - Help menu (this menu)                \n"
                          " r - Reset motors to default position     \n"
                          " f - Toggle feed rate (slow/fast)         \n"
                          " [space] - Stop all motor motion          \n"
                          "                                          \n"
                          "---- Granular Control --------------------\n"
                          "               Gripper up                 \n"
                          "                    I                     \n"
                          " Gripper Close - J  K  L - Gripper Open   \n"
                          "                    |                     \n"
                          "              Gripper Down                \n"
                          "                                          \n"
                          "---- Binary Control ----------------------\n"
                          "               Gripper up                 \n"
                          "                    W                     \n"
                          " Gripper Close - A  S  D - Gripper Open   \n"
                          "                    |                     \n"
                          "              Gripper Down                \n"
                          "==========================================\n";

// Send the help message to specified stream object
void sendHelpMessage(Stream& stream){
    stream.write(helpString);
}

/**
 * @brief Parse commands from the specified stream and trigger necessary actions
 * 
 * @param stream 
 * @return true There are more commands left to be read
 * @return false There are no more commands to be read
 */
bool ParseCommands(Stream& stream){
    if (stream.available()){
        char command = stream.read();
        switch (command){
            // H pressed for 'help'
            case 'H': 
            case 'h':
                sendHelpMessage(stream);
                break;

            // // Stop the motors
            // case ' ':
            //     Gripper.set_motion(GranularServo::STOP);
            //     Lifter.set_motion(GranularServo::STOP);
            //     break;

            // Reset the motors to position
            case 'R':
            case 'r':
                Gripper.write(gripperDefaultAngle);
                Lifter.write(lifterDefaultAngle);
                break;

            // Granular Control
            case 'I':
            case 'i':
                Lifter.write(Lifter.read()-granularIncrementor);
                break;
            case 'K':
            case 'k':
                Lifter.write(Lifter.read()+granularIncrementor);
                break;
            case 'J':
            case 'j':
                Gripper.write(Gripper.read()+granularIncrementor);
                break;
            case 'L':
            case 'l':
                Gripper.write(Gripper.read()-granularIncrementor);
                break;

            // Binary Control
            case 'W':
            case 'w':
                Lifter.write(lifterMinAngle);
                break;
            case 'S':
            case 's':
                Lifter.write(lifterMaxAngle);
                break;
            case 'A':
            case 'a':
                Gripper.write(gripperMaxAngle);
                break;
            case 'D':
            case 'd':
                Gripper.write(gripperMinAngle);
                break;

            // case 'f':
            //     Stepper.moveTo(0);
            //     Serial.println("Move stepper to 0");
            //     break;

            // case 'g':
            //     Stepper.moveTo(500);
            //     Serial.println("Move stepper to 500");
            //     break;
            
            // Ignore other commands
            default:
                break;
        }
    }
    return stream.available();
}

#endif