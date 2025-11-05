#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           slideMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           Gripservo,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port9,           Basketservo,   tmotorServoStandard, openLoop)


/*
Current timer config:
	Timer 1:
	Timer 2:
	Timer 3: Obstacle Detected
	Timer 4: Obstacle Detection Cooldown
*/

int IRValue = 0;

enum RobotState{
		ACTIVE = 0,
		OBSTACLE_DETECTED = 1,
		CHECKING_WEIGHT = 2,
	};


void move(int speed) //range (-180 to 180)
{
	motor[leftMotor] = speed;
	motor[rightMotor] = speed; //flip one of these probably
}

task main()
{
	RobotState currentState = ACTIVE;


	while(1 == 1)
  {
  	if (currentState == ACTIVE){
  		motor[leftMotor] = vexRT[Ch2] / 1.5; // todo: why divide by 1.5 (or multiply by 2/3)
	    motor[rightMotor] = vexRT[Ch3] / 1.5;

	    // Arm Control
			if(vexRT[Btn5U] == 1)       	//If button 5U is pressed...
			{
				motor[armMotor] = 127;    	//...raise the arm.
			}
			else if(vexRT[Btn5D] == 1)  	//Else, if button 5D is pressed...
			{
				motor[armMotor] = -127;   	//...lower the arm.
			}
			else                      		//Else (neither button is pressed)...
			{
				motor[armMotor] = 0;      	//...stop the arm.
			}

	    // Open, close or do not move gripper
			if(vexRT[Btn7U] == 1)       	//If Button 7U is pressed...
			{
				motor[Gripservo] = 127;  		//...close the gripper.
			}
			else if(vexRT[Btn7D] == 1)  	//Else, if button 7D is pressed...
			{
				motor[Gripservo] = -127; 		//...open the gripper.
			}
			else                      		//Else (neither button is pressed)...
			{
				motor[Gripservo] = 0;    		//...stop the gripper.
			}

	    // Open, close or do not move basket
			if(vexRT[Btn8U] == 1)       	//If Button 8U is pressed...
			{
				motor[Basketservo] = 127;  		//...pulls up the basket.
			}
			else if(vexRT[Btn8D] == 1)  	//Else, if button 8D is pressed...
			{
				motor[Basketservo] = -127; 		//...pulls down the basket.
			}
			else                      		//Else (neither button is pressed)...
			{
				motor[Basketservo] = 0;    		//...stop the basket.
			}

				//Slider Control
	    if(vexRT[Btn6U] == 1)
	    {
	      motor[armMotor] = 200;
	    }
	    else if(vexRT[Btn6D] == 1)
	    {
	      motor[armMotor] = -200;
	    }
	    else
	    {
	      motor[armMotor] = 0;
	    }

	    // IR CHECK (account for timer 3)

  	}
    else if(currentState == OBSTACLE_DETECTED){
    	// add a timer
    	clearTimer(T3);
    	while(time1[T3] < 3000)
    	{
    		move(30);
    		// add a cancel button that breaks the loop
    	}
    	currentState = ACTIVE;

    	// start timer 4
    	clearTimer(T4);
    }


  } // while loop end
} // main end
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
