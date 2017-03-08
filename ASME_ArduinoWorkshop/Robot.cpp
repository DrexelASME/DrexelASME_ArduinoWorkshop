/*
 * Library Implementation File for Drexel ASME Arduino Workshop Winter 2017
 * Author: Frederick Wachter - wachterfreddy@gmail.com
 * Date Created: 2017-03-04
 */

#include "Robot.h"

// _____ Public Functions _____

void Robot::runMotors(const int motorSpeed_left, const int motorSpeed_right) {
// Run motors to desired speed and direction
  if (motorSpeed_left != OFF) {
    leftMotor.run(motorState_left);
  }
  if (motorSpeed_right != OFF) {
    rightMotor.run(motorState_right);
  }
}

void Robot::moveForward(const int motorSpeed_left, const int motorSpeed_right) {
// Move the robot forward
  motorState_left = motorState_right = FORWARD;
  setMotorSpeed(motorSpeed_left, motorSpeed_right, _WHEEL_BOTH);
  runMotors(motorSpeed_left, motorSpeed_right);
  Serial.println("[INFO] Robot set to move forward");
}

void Robot::moveBackward(const int motorSpeed_left, const int motorSpeed_right) {
// Move the robot backward
  motorState_left = motorState_right = BACKWARD;
  setMotorSpeed(motorSpeed_left, motorSpeed_right, _WHEEL_BOTH);
  runMotors(motorSpeed_left, motorSpeed_right);
  Serial.println("[INFO] Robot set to move backward");
}

void Robot::spinLeft(const int motorSpeed) {
// Spin the robot in the left direction
  motorState_left  = BACKWARD;
  motorState_right = FORWARD;
  setMotorSpeed(motorSpeed, motorSpeed, _WHEEL_BOTH);
  runMotors(motorSpeed, motorSpeed);
  Serial.println("[INFO] Robot set to spin left");
}

void Robot::spinRight(const int motorSpeed) {
// Spin the robot in the left direction
  motorState_left  = FORWARD;
  motorState_right = BACKWARD;
  setMotorSpeed(motorSpeed, motorSpeed, _WHEEL_BOTH);
  runMotors(motorSpeed, motorSpeed);
  Serial.println("[INFO] Robot set to spin left");
}

void Robot::brake(void) {
// Let the robot coast to a stop
  motorState_left = motorState_right = RELEASE;
  leftMotor.run(motorState_right);
  rightMotor.run(motorState_left);
  Serial.println("[INFO] Robot set to stop");
  delay(500);
}

void Robot::encoderLeft(void) {
// Encoder callback function for left wheel
  if (motorState_left == FORWARD) {
    _encoder_leftTicks++;
  } else {
    _encoder_leftTicks--;
  }
}

void Robot::encoderRight(void) {
// Encoder callback function for right wheel
  if (motorState_right == FORWARD) {
    _encoder_rightTicks++;
  } else {
    _encoder_rightTicks--;
  }
}

void Robot::waitForEncoderLeft(const int goalTicks) {
// Wait until the left motor is at a certain tick value
  Serial.print("[INFO] Waiting for left motor to be at tick count: ");
  Serial.print(goalTicks); Serial.print(", currently at: "); Serial.println(_encoder_leftTicks);
  
  if (goalTicks < _encoder_leftTicks) {
    if (motorState_left == FORWARD) {
      Serial.println("[ERROR] Desired tick value will never be reached");
      return;
    } 
    while (goalTicks < _encoder_leftTicks) {
      Serial.print("[INFO] Left motor tick count: ");
      Serial.println(_encoder_leftTicks); 
    }
  } else {
    if (motorState_left == BACKWARD) {
      Serial.println("[ERROR] Desired tick value will never be reached");
      return;
    } 
    while (goalTicks > _encoder_leftTicks) {
      Serial.print("[INFO] Left motor tick count: ");
      Serial.println(_encoder_leftTicks); 
    }
  }
  
}

void Robot::waitForEncoderRight(const int goalTicks) {
// Wait until the right motor is at a certain tick value
  Serial.print("[INFO] Waiting for left motor to be at tick count: ");
  Serial.print(goalTicks); Serial.print(", currently at: "); Serial.println(_encoder_rightTicks);
  
  if (goalTicks < _encoder_rightTicks) {
    if (motorState_right == FORWARD) {
      Serial.println("[ERROR] Desired tick value will never be reached");
      return;
    } 
    while (goalTicks < _encoder_rightTicks) {
      Serial.print("[INFO] Right motor tick count: ");
      Serial.println(_encoder_rightTicks); 
    }
  } else {
    if (motorState_right == BACKWARD) {
      Serial.println("[ERROR] Desired tick value will never be reached");
      return;
    } 
    while (goalTicks > _encoder_rightTicks) {
      Serial.print("[INFO] Right motor tick count: ");
      Serial.println(_encoder_rightTicks); 
    }
  }
}

void Robot::waitForLeftTicks(const unsigned int ticks) {
// Wait for the left motor to move a certain amount of ticks
  int goalTicks;
  if (motorState_left == BACKWARD) {
    goalTicks = _encoder_leftTicks - ticks;
  } else if (motorState_left == FORWARD) {
    goalTicks = _encoder_leftTicks + ticks;
  } else {
    Serial.println("[ERROR] Attempted to wait for tick counter for left wheel when the left wheel is not moving.");
    return;
  }
  
  Serial.print("[INFO] Waiting for left motor to be at tick count: ");
  Serial.print(goalTicks); Serial.print(", currently at: "); Serial.println(_encoder_leftTicks);
  
  if (goalTicks < _encoder_leftTicks) {
    while (goalTicks < _encoder_leftTicks) {
      Serial.print("[INFO] Left motor tick count: ");
      Serial.println(_encoder_leftTicks); 
    }
  } else {
    while (goalTicks > _encoder_leftTicks) {
      Serial.print("[INFO] Left motor tick count: ");
      Serial.println(_encoder_leftTicks); 
    }
  }
}

void Robot::waitForRightTicks(const unsigned int ticks) {
// Wait for the right motor to move a certain amount of ticks
  int goalTicks;
  if (motorState_right == BACKWARD) {
    goalTicks = _encoder_rightTicks - ticks;
  } else if (motorState_right == FORWARD) {
    goalTicks = _encoder_rightTicks + ticks;
  } else {
    Serial.println("[ERROR] Attempted to wait for tick counter for right wheel when the right wheel is not moving.");
    return;
  }

  Serial.print("[INFO] Waiting for left motor to be at tick count: ");
  Serial.print(goalTicks); Serial.print(", currently at: "); Serial.println(_encoder_rightTicks);
  
  if (goalTicks < _encoder_rightTicks) {
    while (goalTicks < _encoder_rightTicks) {
      Serial.print("[INFO] Right motor tick count: ");
      Serial.println(_encoder_rightTicks); 
    }
  } else {
    while (goalTicks > _encoder_rightTicks) {
      Serial.print("[INFO] Right motor tick count: ");
      Serial.println(_encoder_rightTicks); 
    }
  }
}


// _____ Private Functions _____

void Robot::setupEncoders(void) {
// Setup up interrupts for encoders
  pinMode(ENCODER_LEFT, INPUT_PULLUP);
  pinMode(ENCODER_RIGHT, INPUT_PULLUP);
}

void Robot::setMotorSpeed(const int motorSpeed_left, const int motorSpeed_right, const int wheel) {
// Set the speed of the motors
  if (wheel == _WHEEL_LEFT) {
    leftMotor.setSpeed(motorSpeed_left);
    Serial.print("[INFO] Left motor set to move at speed: ");
  } else if (wheel == _WHEEL_RIGHT) {
    rightMotor.setSpeed(motorSpeed_right);
    Serial.print("[INFO] Right motor set to move at speed: ");
  } else if (wheel == _WHEEL_BOTH) {
    leftMotor.setSpeed(motorSpeed_left);
    rightMotor.setSpeed(motorSpeed_right);
    Serial.print("[INFO] Both motors set to move at speed: ");
  } else {
    Serial.println("[ERROR] Wheel code was not recognized");
    return;
  }
  Serial.print(motorSpeed_left);
  Serial.print(" (left), ");
  Serial.print(motorSpeed_right);
  Serial.println(" (right)");
}


