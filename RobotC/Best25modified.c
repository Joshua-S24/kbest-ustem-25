#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           armMotor,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           slideMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           Gripservo,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port9,           Basketservo,   tmotorServoStandard, openLoop)

typedef enum{
		ACTIVE = 0,
		OBSTACLE_DETECTED = 1,
		CHECKING_WEIGHT = 2,
	} RobotState;

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
  	}
    //Driving Motor Control


  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
