/*

Total Functions Needed:
  - Large Left Motor (Left Wheel):
    - Forward
    - Backward
  - Large Right Motor (Right Wheel):
    - Forward
    - Backward
  - Small Motor 1 (Task unknown):
    - Clockwise
    - Counterclockwise
  - Small Motor 2 (Task unknown):
    - Clockwise
    - Counterclockwise
  - Servo 1 (Task unknown):
    - Clockwise
    - Counterclockwise
  - Servo 2 (Task unknown):
    - Clockwise
    - Counterclockwise
  - Autonomous Factoid Check (1 button)
  - Cancel all auto functions (1 button)

General Notes:

May need a special state for either:
  - Performing any auto func
  - Performing a particular auto func (one state (enum) for each)

Controller oddities:
  Motor output range: 0-180 (stops at 90)
  Servo output range: 0-180
  Joystick X-axis output range: 0-254
    - 0, 127, and 254 represent the max left, center, and max right, respectively
  Joystick Y-axis output range: 0-254
    - 0, 127, and 254 represent the max top, center, and max down, respectively
  Joystick triggers are digital when using DirectInput and analog when using XInput
  Logitech button does not work with DirectInput
  Mode button should NEVER be touched
  D-Pad buttons are analog in DirectInput and are treated as an axis (or joystick), not as 4 buttons
  D-Pad X-axis output range: 0-254
    - 0, 127, and 254 represent the max left, center, and max right, respectively
  D-Pad Y-axis output range: 0-254
    - 0, 127, and 254 represent the max top, center, and max down, respectively
  D-Pad's middle press function is apparently unknown

[CONTROLS] (WIP)

Left Joystick Up/Down - Left Motor Fwd/Rev
Right Joystick Up/Down - Right Motor Fwd/Rev
// new comment

A Button - Check Weight + Cancel

Unused Buttons:
Left Joystick Left/Right
Left Joystick Button
Right Joystick Left/Right
Right Joystick Button
Back Button
Start Button
X Button
Y Button
B Button


[DISREGARD BELOW CONTROLS FOR NOW]


Here are the controls for Arcade Mode:
Left Joystick Up/Down    - Robot Fwd/Rev
Left Joystick Left/Right - Robot Turn Left/Right

These controls work in both modes:
Right Trigger            - Motor 4 Forward
Right Shoulder Button    - Motor 4 Reverse
Left Trigger             - Servo 1 to 0 degrees
Left Shoulder Button     - Servo 1 to 90 degrees

When neither the left trigger nor shoulder button are pressed, the servo will
go to 45 degrees.
*/

#include <Gizmo.h>
#include <Servo.h>
#include <AsyncTimer.h>

Gizmo gizmo;

Servo motor_left;
Servo motor_right;

Servo motor_arm;
Servo servo_task;

bool prev_start_button = false;

// state enums
#define ACTIVE 0
#define CHECKING_WEIGHT 1
#define OBSTACLE_DETECTED 2
int IRlevel;
unsigned long cooldownTime;
unsigned long detectedTime;
bool IRcoolDown = false;
int state = ACTIVE;


void setup() {
  gizmo.begin();


  // Configure the motors & servos for the ports they are connected to

  // Available Motor Ports 1-4
  // Available Servo Ports 1-4

  motor_left.attach(GIZMO_MOTOR_1);
  motor_right.attach(GIZMO_MOTOR_3);
  motor_arm.attach(GIZMO_MOTOR_4);
  servo_task.attach(GIZMO_SERVO_1);

  // Configure the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // INITIAL CHECK-UP

  /* Toggle the built-in LED each time through the loop so we can see
   * that the program really is running.
   */
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  // Refreshes the information about axis and button states
  gizmo.refresh();

  // If the start button was pressed, switch control mode
  bool start_button_pressed = gizmo.getButton(GIZMO_BUTTON_START);
  prev_start_button = start_button_pressed;

  // CHECK-UP END

  if (state == ACTIVE){ // ACTIVE STATE BEGIN
    // Convert gamepad axis positions (0 - 255) to motor speeds (0 - 180)
    motor_left.write(map(gizmo.getAxis(GIZMO_AXIS_LY), 0, 255, 180, 0)); //flipped
    motor_right.write(map(gizmo.getAxis(GIZMO_AXIS_RY), 0, 255, 0, 180));

    // !! All non-wheel motors must be set at (0, 90, or 180)
    // 0 = down, 90 = default, 180 = up

    // Control task motor with right trigger / shoulder button
    if (gizmo.getButton(GIZMO_BUTTON_RT)) {
      motor_arm.write(0);
    }
    else if (gizmo.getButton(GIZMO_BUTTON_RSHOULDER)) {
      motor_arm.write(180);
    }
    else {
      motor_arm.write(90);
    }

    // Control task servo with left trigger / shoulder button
    if (gizmo.getButton(GIZMO_BUTTON_LT)) {
      servo_task.write(0);
    }
    else if (gizmo.getButton(GIZMO_BUTTON_LSHOULDER)) {
      servo_task.write(180);
    }
    else {
      servo_task.write(90);
    }

    if (IRlevel >= 200 && IRcoolDown){
      state = OBSTACLE_DETECTED;
    }
    
    
    // ACTIVE STATE END
  } else if (state == CHECKING_WEIGHT){ // WEIGHT CHECKING STATE BEGIN
      // write a low value (max 90) for the motor speed
      // keep this speed for 3 or less seconds
      // if the button is pressed again, restore control by setting mode to ACTIVE
      
      // WEIGHT CHECK END
    }
    else if (state == OBSTACLE_DETECTED){ // OBSTACLE_DETECTED STATE BEGIN
      // if IR sensor outputs reaches a high integer number
      // stops robot (motor speed = 0) - takes control from operator
      // takes control for at least 0.5 seconds
      // returns to beginning of loop
      // includes a cool down period for about at least 0.5 second
      // uses a bool variable to check the cool down state
      // note: add deceleration later
      if (detectedTime >= 3000){
        motor_left.write(90);
        motor_right.write(90);
      } else{
        state == ACTIVE;
      }
      
      // OBSTACLE_DETECTED STATE END
    }
}
