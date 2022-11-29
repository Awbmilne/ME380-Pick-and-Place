#include <stdint.h>
#include <Arduino.h>

#include "Inputs/Inputs.h"
#include "Outputs/Outputs.h"
#include "Control/CommandParsing.h"
#include "Control/Calibration.h"

void setup() {
    // Configure the Serial object
    pinMode(LED_BUILTIN, OUTPUT);

    // Configure the Serial
    Serial.begin(115200);
    #ifdef ARDUINO_TEENSY40
        while (!Serial){} // Wait for USB Serial to connect
        Serial.println(F("Serial Connected!"));
    #endif
    Serial.println(F("Press any key to enable motors and get started!\n"));

    // Wait for an input on the serial terminal, clear the input then send the help message
    while(true){
        while (!Serial.available()){
            // Blink the LED to show the status
            delay(100);
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        }

        char bit = Serial.read();
        if (bit == 'h' || bit == 'H'){
            Serial.println(F("Serial Connected! Press any key to enable motors and initialize system."));
        }
        else {
            while (Serial.available()) Serial.read();
            break;
        }
    }
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
