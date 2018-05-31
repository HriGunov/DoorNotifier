void Light()
{
	for (int i = 0;i <6;i++)
	{
		strip.SetPixelColor(1, allColors[agitationState + 1]);
		strip.Show();
	}

	delay(200);
	

}

void ResetLights()
{
	for (int i = 0; i<6;i++)
	{
		strip.SetPixelColor(1, defaultNoiseStateColor);
		strip.Show();
	}
}