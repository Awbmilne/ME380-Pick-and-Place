#include <stdint.h>
#include <Arduino.h>

#include "Inputs/Inputs.h"
#include "Outputs/Outputs.h"
#include "Control/CommandParsing.h"
#include "Control/Calibration.h"

void setup() {
    // Configure the Serial object
    Serial.begin(115200);
    #ifdef ARDUINO_TEENSY40
        while (!Serial){} // Wait for USB Serial to connect
    #endif
    Serial.write("Serial Configured!\n\n Press any key to enable motors and get started!\n\n");

    // Wait for an input on the serial terminal, clear the input then send the help message
    while (!Serial.available()) delay(100);
    while (Serial.available()) Serial.read();
    sendHelpMessage(Serial);

    // Setup the Control systems
    Sensor::setup_all();
    GranularControl::setup_all();
}

void loop() {
    Sensor::run_all();

    ParseCommands(Serial);
    run_return_home();
    run_calibration();
    run_auto_cycle();

    GranularControl::run_all();
}
