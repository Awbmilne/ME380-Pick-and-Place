#include <stdint.h>
#include <Arduino.h>

#include "config.h"
#include "Motors.h"
#include "CommandParsing.h"

#undef USE_TIMER_2
#define USE_TIMER_2 true

#include "TimerInterrupt_Generic.h"
#include "ISR_Timer_Generic.h"

uint32_t myTime;

volatile uint32_t timeSum = 0;
volatile uint32_t cycleCount = 0;
volatile uint32_t minTime = UINT32_MAX;
volatile uint32_t maxTime = 0;

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

  ITimer2.init();
  ITimer2.attachInterrupt(refreshRate, GranularServo::run_all, true);
  myTime = millis();
}
 
void loop() {
  ParseCommands(Serial);

  if (millis() - myTime > 5000){
    Serial.print("Minimum run time: "); Serial.print(minTime); Serial.println("μs");
    Serial.print("Maximum run time: "); Serial.print(maxTime); Serial.println("μs");
    Serial.print("Average run time: "); Serial.print(float(timeSum)/cycleCount, 3); Serial.println("μs");
    Serial.println();
    noInterrupts();
      minTime = UINT32_MAX;
      maxTime = 0;
      timeSum = 0;
      cycleCount = 0;
    interrupts();
    myTime = millis();
  }
  // GranularServo::run_all();
  // Stepper.run();
}
