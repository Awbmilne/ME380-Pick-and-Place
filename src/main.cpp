#include <stdint.h>
#include <Arduino.h>

#include "config.h"
#include "Motors.h"
#include "CommandParsing.h"

#undef USE_TIMER_2
#define USE_TIMER_2 true

#include "TimerInterrupt_Generic.h"
#include "ISR_Timer_Generic.h"

void setup() {
  // Configure the Serial object
  Serial.begin(115200);
  Serial.write("Serial Configured!\n\n Press any key to get started!\n\n");

  // Wait for an input on the serial terminal, clear the input then send the help message
  while (!Serial.available()) delay(100);
  while (Serial.available()) Serial.read();
  sendHelpMessage(Serial);

  Gripper.attach(gripperServoPin);
  Lifter.attach(lifterServoPin);

  Gripper.write(gripperDefaultAngle);
  Lifter.write(lifterDefaultAngle);
}
 
void loop() {
  ParseCommands(Serial);
}
