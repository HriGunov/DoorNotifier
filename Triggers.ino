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
	if (held != 0)
	{
		if (held < triggerLimit / 3)
		{
			//Buffer for accidental presses of button
			Serial.println("short");  // the button was released in less than 2sec
		}
		else if (held < triggerLimit / 2)
		{
			//TODO Reset Wifi
			
			Serial.println("medium");  // the button was released in more than 3sec
			
			SendActivation();
			delay(100);
			
		}
		else
		{
			//TODO Reset config
			Serial.println("long");  // the button was released in more than 6 sec

			//work in progress
			/*WiFi.softAPdisconnect();
			WiFi.disconnect();
			ESP.restart();*/
		}
	}

}
bool SoundActivation()
{
	currentSoundLevel = analogRead(soundPin);
	sumOfSound += currentSoundLevel;
	positionInSpan++;


	if (positionInSpan >= ambientSoundSpan)
	{
		ambientSound = sumOfSound / ambientSoundSpan;
		positionInSpan = 0;
		sumOfSound = 0;
	}
	//Debug
	Serial.println("Current sound level: " + String(currentSoundLevel) + " Ambient: " + String(ambientSound));
	Serial.println(String(ambientSoundSpan) + "\\" + String(positionInSpan));
	//Checks if the noise is lould enough
	if (currentSoundLevel > ambientSound + soundActivationThreshold)
	{
		
		return true;
	}
	else false;
}

