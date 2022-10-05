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

            // Stop the motors
            case ' ':
                Gripper.set_motion(GranularServo::STOP);
                Lifter.set_motion(GranularServo::STOP);
                break;

            // Reset the motors to position
            case 'R':
            case 'r':
                Gripper.reset();
                Lifter.reset();
                break;

            // Granular Control
            case 'I':
            case 'i':
                Lifter--;
                break;
            case 'K':
            case 'k':
                Lifter++;
                break;
            case 'J':
            case 'j':
                Gripper++;
                break;
            case 'L':
            case 'l':
                Gripper--;
                break;

            // Binary Control
            case 'W':
            case 'w':
                Lifter.set_angle(Lifter.minAngle);
                break;
            case 'S':
            case 's':
                Lifter.set_angle(Lifter.maxAngle);
                break;
            case 'A':
            case 'a':
                Gripper.set_angle(Gripper.maxAngle);
                break;
            case 'D':
            case 'd':
                Gripper.set_angle(Gripper.minAngle);
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