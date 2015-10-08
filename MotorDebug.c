#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(Motor,     port2,                        rightMotor,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,     port3,                        leftMotor,         tmotorNormal, openLoop)
#pragma config(Motor,     port4,                        fw_right,         tmotorNormal, openLoop)
#pragma config(Motor,     port5,                        fw_left,         tmotorNormal, openLoop)
#pragma config(Motor,     port6,                        intake,         tmotorNormal, openLoop)

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}

void waitForRelease()
{
	while(nLCDButtons != 0)
		wait1Msec(5);
}

// Display Battery Voltage
string mainBattery;
task displayBatteryVoltage
{
	while(true)
	{
		clearLCDLine(1);

		//Display the Primary Robot battery voltage
		displayLCDString(1, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');
		displayNextLCDString(mainBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}

// Flywheel Debugger
task FlywheelTesting
{
	int flywheelPower = 0;
	while(true)
	{
		string display;
		sprintf(display, "Flywheel: ", flywheelPower);
		displayLCDCenteredString(0, display);
		displayLCDString(1, 0, "Less        Moar");

		// Increment or deincrement flywheel speed based on button press
		if(nLCDButtons == leftButton)
		{
			waitForRelease();
			flywheelPower--;
		}
		else if(nLCDButtons == rightButton)
		{
			waitForRelease();
			flywheelPower++;
		}

		if(flywheelPower > 127)
		{
			flywheelPower = 127;
		}
		else if(flywheelPower < -127)
		{
			flywheelPower = -127;
		}

		motor[fw_right] = flywheelPower;
		motor[fw_left] = flywheelPower;
	}
}

// Intake Debugger
task IntakeTesting
{
	int intakePower = 0;
	while(true)
	{
		string display;
		sprintf(display, "Intake: ", intakePower);
		displayLCDCenteredString(0, display);
		displayLCDString(1, 0, "Less        Moar");

		// Increment or deincrement flywheel speed based on button press
		if(nLCDButtons == leftButton)
		{
			waitForRelease();
			intakePower--;
		}
		else if(nLCDButtons == rightButton)
		{
			waitForRelease();
			intakePower++;
		}

		if(intakePower > 127)
		{
			intakePower = 127;
		}
		else if(intakePower < -127)
		{
			intakePower = -127;
		}

		motor[intake] = intakePower;
	}
}

// Drive Debugger
task DriveTesting
{
	int drivePower = 0;
	while(true)
	{
		string display;
		sprintf(display, "Drive: ", drivePower);
		displayLCDCenteredString(0, display);
		displayLCDString(1, 0,"Less        Moar");

		// Increment or deincrement flywheel speed based on button press
		if(nLCDButtons == leftButton)
		{
			waitForRelease();
			drivePower--;
		}
		else if(nLCDButtons == rightButton)
		{
			waitForRelease();
			drivePower++;
		}

		if(drivePower > 127)
		{
			drivePower = 127;
		}
		else if(drivePower < -127)
		{
			drivePower = -127;
		}

		motor[rightMotor] = drivePower;
		motor[leftMotor] = drivePower;
	}
}



/*                                                                        */
/*                           Code that Selects                            */
/*                                                                        */
task main()
{

	//Declare count variable to keep track of our choice
	int count = 0;

	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options
		switch(count)
		{
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Flywheel Testing" );
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Intake Testing");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Drive Testing");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Battery Voltage");
			displayLCDCenteredString(1, "<         Enter        >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 0;
			}
			break;
		default:
			count = 0;
			break;
		}
	}



	/*                                                                        */
	/*                               Code that Runs                           */
	/*                                                                        */

	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);

	//Switch Case that actually runs the user choice
	switch(count)
	{
	case 0:
		//If count = 0, run the code correspoinding with choice 1
		displayLCDCenteredString(0, "Flywheel Testing");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(1000);
		startTask(FlywheelTesting);
		break;

	case 1:
		//If count = 1, run the code correspoinding with choice 2
		displayLCDCenteredString(0, "Intake Testing");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(1000);
		startTask(IntakeTesting);
		break;

	case 2:
		//If count = 2, run the code correspoinding with choice 3
		displayLCDCenteredString(0, "Drive Testing");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(1000);
		startTask(DriveTesting);
		break;

	case 3:
		//If count = 3, run the code correspoinding with choice 4
		displayLCDCenteredString(0, "Battery Voltage:");
		startTask(displayBatteryVoltage);
		break;

	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}

	// Keep the Program Running
	while(true){ wait1Msec(25); }
}
