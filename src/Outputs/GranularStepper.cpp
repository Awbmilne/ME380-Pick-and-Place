
#include "GranularStepper.h"

#include "config.h"
#include "utilities.h"

/**
 * @brief Configure the stepper and prepair for movement
 * 
 */
void GranularStepper::setup(){
    _stepper.enableOutputs();
}

/**
 * @brief Return the stepper to the home angle position
 * 
 */
void GranularStepper::home(){
    set_angle(homeAngle);
}

/**
 * @brief Check of the stepper is moving
 * 
 * @return bool
 */
bool GranularStepper::moving(){
    return _stepper.isRunning();
}

/**
 * @brief Get the current angle of the stepper motor output
 * 
 * @return float The current angle in absolute degrees
 */
float GranularStepper::get_angle(){
    return step_to_angle(_stepper.currentPosition());
}

/**
 * @brief Set the target angle for the stepper motor output
 * 
 * @param angle The angle in degrees
 */
void GranularStepper::set_angle(float angle){
    set_angle(angle, maxSpeed);
}

/**
 * @brief Set the target angle for the stepper motor output
 * 
 * @param angle The angle in degrees
 * @param percent The percent of max speed to operate at
 */
void GranularStepper::set_anglep(float angle, float percent){
    set_angle(angle, maxSpeed*percent);
}

/**
 * @brief Set the target angle for the stepper motor output
 * 
 * @param angle 
 * @param rate 
 */
void GranularStepper::set_angle(float angle, float rate){
    set_speed(rate);
    _stepper.moveTo(angle_to_step(constrain(angle, minAngle, maxAngle)));
}

/**
 * @brief Set the stepper speed as a percent of the max speed
 * 
 * @param percent The percent of the maximum speed
 */
void GranularStepper::set_speedp(float percent){
    set_speed(maxSpeed*percent);
}

/**
 * @brief Set the speed for which to operate the stepper
 * 
 * @param rate The rate to operate the stepper at
 */
void GranularStepper::set_speed(float rate){
    _stepper.setMaxSpeed(angle_to_step(constrain(rate, 0, maxSpeed)));
}

/**
 * @brief Start the stepper moving in the specified direction
 * 
 * The stepper will move in the specified direction (or stop)
 * until max/min position is reached.
 * 
 * @param dir The direction to move
 * @param rate The speed to operate at
 */
void GranularStepper::set_motion(direction dir, float rate){
    set_speed(rate);
    set_motion(dir);
}

/**
 * @brief Start the stepper moving in the specified direction
 * 
 * The stepper will move in the specified direction (or stop)
 * until max/min position is reached.
 * 
 * @param dir The direction to move
 * @param percent The percent of max speed to operate at
 */
void GranularStepper::set_motionp(direction dir, float percent){
    set_speed(maxSpeed*percent);
    set_motion(dir);
}

/**
 * @brief Start the stepper moving in the specified direction
 * 
 * The stepper will move in the specified direction (or stop)
 * until max/min position is reached.
 * 
 * @param dir The direction to move
 */
void GranularStepper::set_motion(direction dir){
    switch(dir){
        case direction::CW:
            _stepper.moveTo(angle_to_step(maxAngle));
            break;
        case direction::CCW:
            _stepper.moveTo(angle_to_step(minAngle));
            break;
        case direction::STOP:
            stop();
            break;
    }
}

/**
 * @brief Set the current position as the calibration positiion
 * 
 */
void GranularStepper::set_calibrate(){
    _stepper.setCurrentPosition(angle_to_step(calibrationAngle));
}

/**
 * @brief Overload the ++ operator to increment the stepper's position
 * 
 */
void GranularStepper::operator++(int){
    _stepper.move(angle_to_step(incrementor));
}

/**
 * @brief Overload the -- operator to decrement the stepper's position
 * 
 */
void GranularStepper::operator--(int){
    _stepper.move(angle_to_step(-incrementor));
}

/**
 * @brief Run the stepper motor. Take a step if necessary,
 * based on speed and acceleration.
 * 
 */
void GranularStepper::run(){
    _stepper.run();
}

/**
 * @brief Stop the stepper motor as fast as possible,
 * remaining without the acceleration limit to not lose
 * steps.
 * 
 */
void GranularStepper::stop(){
    _stepper.stop();
}

/**
 * @brief Convert step value to angle value
 * 
 * @param step The step in a 360 rotation
 * @return float The angle that corresponds
 */
float GranularStepper::step_to_angle(long step){
    return (step / stepsPerRev);
}

/**
 * @brief Convert step value to angle value
 * 
 * @param angle The angle in a 360 rotation
 * @return long The step that corresponds
 */
long GranularStepper::angle_to_step(float angle){
    return (angle * stepsPerRev);
}
