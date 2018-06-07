void Light(int intentsity)
{
	int level = 0;
	if (intentsity < 50)
	{
		level = 0;
	}
	else if (intentsity < 150)
	{
		level = 1;
	}
	else if (intentsity < 350)
	{
		level = 2;
	}
	else  
	{
		level = 3;
	}
	 

	for (int i = 0;i < 6;i++)
	{
		strip.SetPixelColor(i, allColors[level]);
		strip.Show();
	}

	delay(200);
}

void ResetLights()
{
	for (int i = 0; i<6;i++)
	{
		strip.SetPixelColor(i, defaultNoiseStateColor);
		strip.Show();
	}
}