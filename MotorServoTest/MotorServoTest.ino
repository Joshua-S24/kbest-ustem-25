#include <Gizmo.h>
#include <Servo.h>

Gizmo gizmo

Servo motor_left;
Servo motor_right;

Servo servo_1;
Servo servo_2;

/*
The purpose of this script is to help with testing motor speeds and servo configurations through a consistent means.
Regarding motors, the main code for the robot currently handles a varying magnitude of input based on the strength of the joystick input.
  In other words, the speed of the robot's motor varies with how far the joystick is pushed.
This script allows for the motors to rotate at a consistent speed.
This script also supports servo rotation (although this is not as necessary)

Explanation:
  leftSpeed and rightSpeed should be set within 0-90.
  (leftSpeed and rightSpeed will be collectively referred to as motorSpeed).
  When the corresponding joystick axis is pushed *upward* it will write the sum of motorSpeed and 90 to the motor (motorSpeed + 90).
  When the corresponding joystick axis is pushed *downward* it will write the difference of 90 and the motorSpeed to the motor (90 - motorSpeed).
  The reason for this is because Servo.write() only accepts ints from 0-180.
    Servo.write(180) rotates the motor counterclockwise at full speed.
    Servo.write(0) rotates the motor clockwise at full speed.
    Servo.write(90) stops the motor
  In other words:
    motorSpeed = 90 means...
      joystick downward -> 0
      joystick upward -> 180
    motorSpeed = 45 means...
      joystick downward -> 45
      joystick upward -> 135
*/

// note: mess with microseconds later

// Servo Enums
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define SERVO_1 2
#define SERVO_2 3
// TODO: add two new servo enums

int selectedServo = LEFT_MOTOR; // dictates the current servo 

// Servo Speeds
// These variables store the current speed 
int leftMotorSpeed = 90; // corresponds to LEFT_MOTOR
int rightMotorSpeed = 90; // corresponds to RIGHT_MOTOR
int servo1Angle = 90; // corresponds to SERVO_1
int servo2Angle = 90; // corresponds to SERVO_2
// TODO: add two new variables for two servos

// Button Speed Values
// These variables dictate the values that can be written to any given servo.
// For example, pressing the A button while AButtonSpeed = 23 will set the servo's speed variable to 23.
int AButtonSpeed = 23;
int BButtonSpeed = 46;
int XButtonSpeed = 69;
int YButtonSpeed = 90;


void setup() {
  // put your setup code here, to run once:
  gizmo.begin();
  motor_left.attach(GIZMO_MOTOR_1);
  motor_right.attach(GIZMO_MOTOR_3);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  int leftJoystickAxis = gizmo.getAxis(GIZMO_AXIS_LY);
  int rightJoystickAxis = gizmo.getAxis(GIZMO_AXIS_RY);
  
  if (leftJoystickAxis > 200){ // within 55 units of max input strength (up)
    motor_left.write(90 + leftMotorSpeed);
  }
  else if (leftJoystickAxis < 55){
    motor_left.write(90 - leftMotorSpeed);
  }

  if (rightJoystickAxis > 200){
    motor_right.write(90 - rightMotorSpeed);
  } else if (rightJoystickAxis < 55){
    motor_right.write(90 + rightMotorSpeed);
  }

  // Motor Selecting Buttons
  // The LT and RT buttons will set the selected servo to the left motor and right motor respectively.
  // The D-Pad (refer to D-Pad analog controls) will set the selected servo to one of the 4 servos.
  // TODO: finish this for the right motor and servos (difficult)
  // also the LB button broke
  if (gizmo.getButton(GIZMO_BUTTON_LT)){
    selectedServo = LEFT_MOTOR;
  } else if (gizmo.getButton(GIZMO_BUTTON_RT)){

  }
  
  // Speed Setting Buttons
  // The 4 buttons (A, B, X, Y) can set the selected servo to different speeds
  // For example, pressing the A button while selectedServo = LEFT_MOTOR sets leftMotorSpeed to (the value of) AButtonSpeed.
  if (gizmo.getButton(GIZMO_BUTTON_A)) {
    // TODO: create an if statement for every enum
    if (selectedServo == LEFT_MOTOR){
      leftMotorSpeed = AButtonSpeed;
    } else if (selectedServo == RIGHT_MOTOR){
      
    }
  }
  

  
  
}
