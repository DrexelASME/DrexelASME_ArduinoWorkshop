/*
 * Library Header File  for Drexel ASME Arduino Workshop Winter 2017
 * Author: Frederick Wachter - wachterfreddy@gmail.com
 * Date Created: 2017-03-04
 */

#ifndef ASME_ARDUINO_WORKSHOP
#define ASME_ARDUINO_WORKSHOP

#include "Arduino.h"
#include "AFMotor.h"

#define OFF 0 // motor off speed
#define SLOW 150 // motor slow speed
#define MEDIUM 200 // motor medium speed
#define FAST 250 // motor fast speed

#define ENCODER_LEFT 3 // left motor encoder signal pin
#define ENCODER_RIGHT 2 // right motor encoder signal pin
#define TICKS_PER_REVOLUTION 20 // ticks per revolution

class Robot {
  public:
    // Variables
    AF_DCMotor leftMotor  = 3; // left motor is attached to motor 3 slot
    AF_DCMotor rightMotor = 4; // right motor is attached to motor 4 slot
    
    long int motorState_left  = RELEASE; // direction of left wheel
    long int motorState_right = RELEASE; // direction of right wheel
      
    // Default Constructor
    Robot(void) { setupEncoders(); };

    // Public Functions
    void runMotors(const int, const int); // run motors to desired speed and direction
    void moveForward(const int, const int); // move the robot forward
    void moveBackward(const int, const int); // move the robot backward
    void spinLeft(const int); // spin robot in left direction
    void spinRight(const int); // spin robot in right direction
    void brake(void); // stop the robot by coasting

    void encoderLeft(void); // callback function for the left encoder
    void encoderRight(void); // callback function for the right encoder
    void waitForEncoderLeft(const int); // wait until the left motor is at a certain tick value
    void waitForEncoderRight(const int); // wait until the right motor is at a certain tick value
    void waitForLeftTicks(const unsigned int); // wait for the left motor to move a certain amount of ticks
    void waitForRightTicks(const unsigned int); // wait for the right motor to move a certain amount of ticks
  private:
    // Private Variables
    const int _WHEEL_RIGHT = 0; // indicates if only the right wheel is set to move
    const int _WHEEL_LEFT  = 1; // indicates if only the left wheel is set to move
    const int _WHEEL_BOTH  = 2; // indicates if both wheels is set to move
    
    long int _encoder_leftTicks  = 0; // keep track of position of left wheel
    long int _encoder_rightTicks = 0; // keep track of position of right wheel

    // Private Functions
    void setupEncoders(void); // setup encoder
    void setMotorSpeed(const int, const int, const int); // set the motor speed
};

#endif



