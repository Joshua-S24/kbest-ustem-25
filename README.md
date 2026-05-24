# Veritas

!\[Veritas](Photos/Veritas)

This is a public repository for the Kerr Engineering Club's 2025 Flagship Robot: Veritas. Veritas was built for the purpose of competing in the head-to-head competition in the Boosting Engineering Science and Technology (BEST) Robotics 2025 Competition: Factoids, where we competed in the Urban STEM hub.

### Programming

#### Arduino C++

The programming of Veritas first started with the Gizmo, the educational microcontroller that was provided by our hub. Because the Gizmo uses a Raspberry Pi Pico for student programming, we could have used either MicroPython or the Arduino IDE. Because we had programmed the Gizmo using the Arduino IDE in the last competition, it was best to continue using Arduino C++ to program Veritas.

##### Controls

The controls of the robot were arguably the most important task for the programming team. This is because the controls must be configured in a way that is intuitive and easy to understand for operators.

###### Controller

We were given a Logitech F310 wired joystick controller.

!\[Logitech](Photos/LogitechF130\_Controller)

At one point, one of the shoulder buttons became faulty, which required some adjustments with the controls, although this didn't matter in the long run.

###### Mobility

Veritas had 4 wheels, with two motors being dedicated to the front drive wheels. The default code provided by BEST Robotics had an Arcade mode and a Tank mode for mobility. Arcade mode configured movement to the left joystick.

**Arcade Mode Controls:**

* Up = Forward
* Down = Backward
* Left = Turn Left
* Right = Turn Right

Tank mode dedicated a joystick to each wheel.

**Tank Mode Controls:**

* Left Joystick Up = Left Wheel Clockwise
* Left Joystick Down = Left Wheel Counterclockwise
* Right Joystick Up = Right Wheel Clockwise
* Right Joystick Down = Right Wheel Counterclockwise

Most of our team members were more familiar with the tank drive mode. Additionally, tank mode offered more precision in movement to make up for the extra joystick. With that in mind, the arcade mode was removed, which freed up the Mode button.

###### Arm Controls

The arm's movement was dedicated to the "D-Pad" of each controller, which was otherwise the 4 buttons to the left. The arm also had a claw that was intended to grab objects with the help of a servo. The grip button was dedicated to the A Button, or the rightmost button on the front of the controller.

**Arm Controls:**

* Left = Rotate Arm Counterclockwise
* Right = Rotate Arm Clockwise
* Up = Raise Arm
* Down = Lower Arm
* A Button = Toggle Grip Servo

##### IR Sensing

Because our hub provided an IR sensor, it was originally to be used for collision detection. There was originally code for a state machine that temporarily took control away from the operator to perform a corrective maneuver and prevent damage. This state machine would have also been the foundation for any autonomous actions that the robot could perform without the operator's input. However, the IR sensor was unused due to time constraints combined with a lack of priority, and Veritas did not have any features that would justify autonomous actions. To keep the program simple, the code was deprecated.

#### RobotC

After an incident concerning the Gizmo, we were forced to use the VEX Cortex microcontroller instead. This also meant that the code written up until that point needed to be transferred over to RobotC. Because of our prior experience with RobotC, translating the movement controls from Arduino C++ to RobotC was not difficult. The code for the IR Sensor was also able to be transferred, but by this point, it was deprecated due to a lack of necessity. In its place, a new mode was created, inspired by the mode switch that the default code had.

##### Controls

###### Controller

To use the VEX Cortex microcontroller, we needed a different controller: the VEXnet controller.

!\[VEXnet](Photos/VEXnet\_Controller)

The locations of the buttons mimicked the previous controller, so transferring the mobility controls was made even easier. Additionally, using wireless controls proved to be easier with this microcontroller, as it only required two VEXnet Keys.

###### Reverse Mode

As mentioned before, the controls were kept faithful to the previous version. One new feature was fully developed by this time: the reverse mode. During operation, controlling Veritas while it was backwards proved to be difficult. While learning to control Veritas backwards could be learned, it would be far easier for the operators if there was a way to toggle reversed controls. Therefore, button 8U was dedicated to reversing the controls. However, on competition day, there were problems with toggling this mode. This may have had to do with the fact that this code was kept within a while loop, meaning that for *every iteration* button 8U was pressed, the reverse button would flip itself. There is also no way of knowing how the controllers were oriented unless the operator attempted to move Veritas. In retrospect, it may have been easier to dedicate two buttons to turn reverse mode on and off, but it was removed on the day of the competition.

###### Grip Servo

On the first version, the A button was meant to toggle the grip of the servo. Due to the nature of while loops, this did not work. Instead, this button was changed so that the operator had to hold the button to close the grip of the arm.

### VEXcode V5

Upon advancing to the State UIL competition, we were given a VEX V5 brain that needed to replace our current microcontroller, whether it was the Gizmo or the VEX Cortex. This microcontroller was undoubtedly an upgrade, as it contained more features, like new ports, or the capability to store multiple scripts. Finally, the VEX V5 brain had its own IDE, which could be used on an online website or an offline app. This supported block-based coding, C++, and Python. Again, based on prior experience, C++ was chosen.

##### Controls

###### Controller

The VEX V5 brain also came with a new controller.

!\[VEXV5](Photos/VEXV5\_Controller)

This controller was more modern than any of the previous controllers we've handled. Convenient features aside, the controller interface could be programmed and customized during run time. This meant that we had a way to display information. This feature was mainly used to give operators an indicator of if reverse mode was toggled, which was previously impossible.

###### Reverse Mode

The switch to VEXcode V5 meant that there were now functions that made it easy to remove the reverse mode code from the while loop. Thanks to this, reverse mode was reinstated, becoming more intuitive for operators.

