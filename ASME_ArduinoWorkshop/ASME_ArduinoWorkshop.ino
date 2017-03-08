#include "Robot.h"

// Variables - DO NOT CHANGE
Robot robot;

// Function Prototypes - DO NOT CHANGE
void exampleLoop(void);

// Encoder Functions - DO NOT CHANGE
void encoderLeft(void) { robot.encoderLeft(); }
void encoderRight(void) { robot.encoderRight(); }

void setup() {
  // Setup Communication from Arduino at Arduino Uno Baud Rate - DO NOT CHANGE
  Serial.begin(9600);

  // Setup Encoder Interrupt Functions - DO NOT CHANGE
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), encoderLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), encoderRight, RISING);
}

/* _____ Important Information _____
 * ___ Robot Speeds (Asll caps is neccessary) ___
 *     OFF, SLOW, MEDIUM, FAST
 *
 * ___ Movement Functions ___
 *     robot.moveForward(motorSpeed_left, motorSpeed_right);
 *     robot.moveBackward(motorSpeed_left, motorSpeed_right);
 *     robot.spinLeft(motorSpeed);
 *     robot.spinRight(motorSpeed);
 *     robot.brake();
 *    
 *   Variable Meanings:
 *     motorSpeed_left  - left motor speed desired (OFF, SLOW, MEDIUM, FAST)
 *     motorSpeed_right - right motor speed desired (OFF, SLOW, MEDIUM, FAST)
 *     motorSpeed       - both motor speeds desired (OFF, SLOW, MEDIUM, FAST)
 *    
 * ___ Delay Functions ___
 *     robot.waitForLeftTicks(deltaTicks); - This is easier to use
 *     robot.waitForRightTicks(deltaTicks); - This is easier to use
 *     robot.waitForEncoderLeft(tick);
 *     robot.waitForEncoderRight(tick);
 *     delay(milliseconds);
 *    
 *   Variable Meanings:
 *     deltaTicks    - The change in ticks from the point where the function is run until the
 *                     desired change in ticks is reached. This number should always be positive
 *     ticks         - The desired tick position of the encoder that you would like to keep the
 *                     robot running until that tick value is reached
 *     millisections - amount of time the program will wait in milliseconds the program will wait
 *                     before executing the next line
 *                  
 *   Relevant Information:               
 *     20 ticks per revolution
 */

void loop() {
  // Your code goes here

  // Try this example by uncommenting the line below:
  // exampleMovement();
}


// _____ EXAMPLE FUNCTIONS _____

// Example Loop Function - DO NOT CHANGE
void exampleMovement(void) {
  // Move Forward for 50 Encoder Ticks on Left Wheel then Brake
  robot.moveForward(MEDIUM, MEDIUM);
  robot.waitForLeftTicks(50);
  robot.brake();

  // Spin Left for 50 Encoder Ticks on Right Wheel then Brake
  robot.spinLeft(MEDIUM);
  robot.waitForRightTicks(15);
  robot.brake();

  // Move Backward for 50 Encoder Ticks on Left Wheel then Brake
  robot.moveBackward(FAST, FAST);
  robot.waitForRightTicks(50);
  robot.brake();

  // Spin Right for 50 Encoder Ticks on Right Wheel then Brake
  robot.spinLeft(MEDIUM);
  robot.waitForRightTicks(15);
  robot.brake();
}



