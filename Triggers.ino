bool CheckTriggered()
{
	isTriggered = digitalRead(FLASH_BUTTON);
	if (isTriggered == LOW)
		return true;
	return false;
}

//Locks execution of loop 
int const triggerLimit = 60;
int ButtonIntensity()
{
	int held = 0;
	
	while (CheckTriggered() && held < triggerLimit)
	{
		delay(100);
		held++;
	}
	if (held < triggerLimit/3)
	{
		//Buffer for accidental presses of button
		Serial.println("short");  // the button was released in less than 2sec
	}
	else if (held < triggerLimit / 2)
	{
		//TODO Reset Wifi
		Serial.println("medium");  // the button was released in more than 3sec

	}
	else if  
	{
		//TODO Reset config
		Serial.println("long");  // the button was released in more than 6 sec

	}
}


