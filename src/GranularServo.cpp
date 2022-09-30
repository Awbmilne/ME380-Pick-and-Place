
#include "GranularServo.h"

// CLAMP a value between the lower and upper limit
template <typename T> T CLAMP(const T& value, const T& low, const T& high) 
{
  return value < low ? low : (value > high ? high : value); 
}

/**
 * @brief Configure the servo and move to default position
 */
void GranularServo::setup(){
    servo.attach(servoPin);
    set_speed(maxSpeed/2);
    set_angle(defaultAngle);
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
 * @brief Operate the servo
 * 
 */
void GranularServo::run(){
    // Update the position using a time delta
    if (position != goal){
        float maxStep = speed * (time - millis()) * (1.0/1000);
        position += CLAMP(goal - position, -maxStep, maxStep); ;
    }
    // Set the servo position using the configured parameters
    servo.writeMicroseconds(CLAMP(uint32_t((position / travel) * (maxPulse - minPulse) + minPulse), minPulse, maxPulse));
    // Reset the time tracking variable
    time = millis();
}
