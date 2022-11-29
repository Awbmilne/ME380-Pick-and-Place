
#include <Arduino.h>

#include "GranularServo.h"

#include "utilities.h"
#include "config.h"

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
    set_angle(defaultAngle, true);
    time = millis();

    digitalWrite(enablePin, enableState == LOW ? LOW : HIGH);
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
 * @brief Check if the servo is currently moving
 * 
 * @return bool
 */
bool GranularServo::moving(){
    return (position != goal);
}

/**
 * @brief Set the angle for the servo to move to
 * 
 * @param angle Angle to move to
 */
void GranularServo::set_angle(float angle, bool bypass_speed){
    // Set the angle within the clamped range
    goal = CLAMP(angle, minAngle, maxAngle);
    // Force instant position update if required
    if (bypass_speed){
        position = goal;
        run(true);
    }
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
            run(); // force update the PWM signal
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
 * @brief Overload the ++ operator to increment the servo's position
 * 
 */
void GranularServo::operator++(int){
    set_angle(get_angle() + incrementor);
}

/**
 * @brief Overload the -- operator to decrement the servo's position
 * 
 */
void GranularServo::operator--(int){
    set_angle(get_angle() - incrementor);
}

/**
 * @brief Operate the servo, make adjustments if needed
 * 
 */
void GranularServo::run(){
    run(false);
}

/**
 * @brief Operate the servo, make adjustments if needed
 * 
 * @param force Force an update of the servos PWM, ignoring refresh rate
 */
void GranularServo::run(bool force_update){
    // Only run at the refresh rate
    if (millis()-time > (1000.0F / refreshRate) || force_update){
        // Update the position using a time delta
        if (position != goal){
            float maxStep = speed * (millis()-time) * (1.0F/1000);
            position += CLAMP(goal - position, -maxStep, maxStep); ;
        }
        #ifdef ARDUINO_TEENSY40
            // Write the servos position, limiting to whole angles in range
            if (!invert)
                servo.write(CLAMP((double)position, (double)ceil(minAngle), (double)floor(maxAngle)));
            else
                servo.write(CLAMP(double(travel)-(double)position, (double)ceil(minAngle), (double)floor(maxAngle)));
        #else
            // Set the servo position using the configured parameters
            if (!invert)
                servo.writeMicroseconds(CLAMP(uint32_t((position / travel) * (maxPulse - minPulse) + minPulse), minPulse, maxPulse));
            else
                servo.writeMicroseconds(CLAMP(maxPulse - uint32_t((position / travel) * (maxPulse - minPulse)), minPulse, maxPulse));
        #endif
        // Reset the time tracking variable
        time = millis();
    }
}

/**
 * @brief Output the Servo's position
 * 
 * @param stream 
 */
void GranularServo::output(Stream& stream){
    char vals[3][6] = {};
    dtostrf(minAngle, 5, 1, vals[0]);
    dtostrf(position, 5, 1, vals[1]);
    dtostrf(maxAngle, 5, 1, vals[2]);
    const static char output_string[] PROGMEM = "%7s Servo:   %5s, %5s, %5s";
    char buffer[37];
    snprintf_P(buffer, sizeof(buffer), output_string, name, vals[0], vals[1], vals[2]);
    stream.println(buffer);
}
