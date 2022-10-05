#include <stdint.h>
#include <Arduino.h>

#include "Motors.h"
#include "CommandParsing.h"


void setup() {
  // Configure the Serial object
  Serial.begin(115200);
  Serial.write("Serial Configured!\n\n Press any key to get started!\n\n");

  // Wait for an input on the serial terminal, clear the input then send the help message
  while (!Serial.available()) delay(100);
  while (Serial.available()) Serial.read();
  sendHelpMessage(Serial);

  // Initialize the motors
  Gripper.setup();
  Lifter.setup();

  Stepper.setMaxSpeed(1000);
  Stepper.setAcceleration(200);
  // Stepper.moveTo(0);
}
 
void loop() {
  ParseCommands(Serial);
  Gripper.run();
  Lifter.run();
  // Stepper.run();
}
