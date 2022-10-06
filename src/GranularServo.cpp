
#include "GranularServo.h"

#include "config.h"
#include "utilities.h"

GranularServo* GranularServo::first = nullptr;

/**
 * @brief Construct a new Granular Servo object
 * 
 * @param servoPin The PWM pin for controlling the servo
 * @param maxSpeed The software limited speed of the
 * @param defaultAngle The default angle for the servo, used at startup
 * @param minAngle The software enforced min angle limit
 * @param maxAngle The software enforced max angle limit
 * @param travel The physical travel limit of the servo for the pulse range
 * @param minPulse Minimum PWM pulse length
 * @param maxPulse Maximum PWM pulse length
 */
GranularServo::GranularServo(uint8_t servoPin,
                             float defaultAngle,
                             float defaultSpeed,
                             float minAngle,
                             float maxAngle,
                             float maxSpeed,
                             float travel,
                             uint32_t minPulse,
                             uint32_t maxPulse):
                             servoPin(servoPin),
                             defaultAngle(defaultAngle),
                             defaultSpeed(defaultSpeed),
                             minAngle(minAngle),
                             maxAngle(maxAngle),
                             maxSpeed(maxSpeed),
                             travel(travel),
                             minPulse(minPulse),
                             maxPulse(maxPulse){
    // Add the object to the linked list of
    if (first == nullptr){
        first = this;
    }
    else{
        GranularServo* current = first;
        while(current->next != nullptr) current = current->next;
        current->next = this;
    }
}

/**
 * @brief Safely destroy the GranularServo::GranularServo object
 * 
 */
GranularServo::~GranularServo(){
    // Remove the pointer from the single linked-list of objects
    if (first == this){
        if (this->next != nullptr) first = this->next;
        else first = nullptr;
    }
    else{
        GranularServo* previous = first;
        GranularServo* current = previous->next;
        while (current != this){
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }
}

/**
 * @brief Configure the servo and move to default position
 */
void GranularServo::setup(){
    #ifndef ARDUINO_TEENSY40
        servo.attach(servoPin);
    #else
        servo.attach(servoPin, minPulse, maxPulse);
    #endif
    set_speed(defaultSpeed);
    set_angle(defaultAngle);
    time = millis();
}


/**
 * @brief Get the servo's current position
 * 
 * @return float Servo position in degrees
 */
float GranularServo::get_angle(){
    return position;
}

/**
 * @brief Set the angle for the servo to move to
 * 
 * @param angle Angle to move to
 */
void GranularServo::set_angle(float angle){
    // Set the angle within the clamped range
    goal = CLAMP(angle, minAngle, maxAngle);
}

/**
 * @brief Set the speed of the servo
 * 
 * @param speed Speed to move servo at [deg/sec]
 */
void GranularServo::set_speed(float speed){
    // Limit the speed to the max speed
    this->speed = CLAMP(speed, 0.0F, maxSpeed);
}

/**
 * @brief Set the speed of the servo as a percent of max speed
 * 
 * @param speed Proportional speed to move servo at [0.0 <-> 1.0]
 */
void GranularServo::set_speedp(float speed){
    // Limit the range of the value
    speed = maxSpeed * CLAMP(speed, 0.0F, 1.0F);
}

/**
 * @brief Start the servo moving freely, until the limit
 * 
 * @param dir The direction to move the servo (or stop)
 */
void GranularServo::set_motion(direction dir){
    switch (dir){
        case(STOP):
            goal = position; // Set the current position as the goal
            run(true); // force update the PWM signal
            break;
        case(CW):
            goal = maxAngle; // Set the goal as the maxAngle
            break;
        case(CCW):
            goal = minAngle; // Set the goal as the minAngle
            break;
    }
}

/**
 * @brief Start the servo moving freely at a certain speed, until the limit
 * 
 * @param dir The direction to move the servo (or stop)
 * @param rate Speed to move servo at [deg/sec]
 */
void GranularServo::set_motion(direction dir, float rate){
    set_speed(rate);
    set_motion(dir);
}

/**
 * @brief Overload the ++ operator to increment the servos position
 * 
 */
void GranularServo::operator++(int){
    set_angle(get_angle() + granularIncrementor);
}

/**
 * @brief Overload the -- operator to decrement the servos position
 * 
 */
void GranularServo::operator--(int){
    set_angle(get_angle() - granularIncrementor);
}

/**
 * @brief Operate the servo, make adjustments if needed
 * 
 * @param force Force an update of the servos PWM, ignoring refresh rate
 */
void GranularServo::run(bool force){
    // Only run at the refresh rate
    if (millis()-time > (1000.0F / refreshRate) || force){
        // Update the position using a time delta
        if (position != goal){
            float maxStep = speed * (millis()-time) * (1.0F/1000);
            position += CLAMP(goal - position, -maxStep, maxStep);
        }
        #ifdef ARDUINO_TEENSY40
            // Write the servos position, limiting to whole angles in range
            servo.write(CLAMP(position, ceil(minAngle), floor(maxAngle)));
        #else
            // Set the servo position using the configured parameters
            servo.writeMicroseconds(CLAMP(uint32_t((position / travel) * (maxPulse - minPulse) + minPulse), minPulse, maxPulse));
        #endif
        // Reset the time tracking variable
        time = millis();
    }
}

/**
 * @brief Call the run() function for all created servo objects
 * 
 */
void GranularServo::run_all(bool force){
    uint32_t time = micros();
    GranularServo* current = first;
    while (current != nullptr){
        current->run(force);
        current = current->next;
    }
    uint32_t delay = micros() - time;
    if (delay < minTime) minTime = delay;
    if (delay > maxTime) maxTime = delay;
    timeSum += delay;
    cycleCount++;
}
