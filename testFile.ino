bool CheckTriggered()
{
  isTriggered = digitalRead(FLASH_BUTTON);
  if(isTriggered == LOW)
    return true;
  return false;
}

int ActivityIntensity()
{
    
} 


