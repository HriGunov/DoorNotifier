
#pragma region NeoPixelSetUp


//RainbowStrip

#include <NeoPixelBus.h>
const uint16_t PixelCount = 6; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266

#define Cred     RgbColor(255, 0, 0)
#define Cblue    RgbColor(0, 0, 255)
#define Cgreen   RgbColor(0, 255, 0)
#define Cyellow  RgbColor(255, 255, 0)
#define Corange  RgbColor(255, 100, 0)
#define Cwhite   RgbColor(255, 255, 255)
#define Cblack   RgbColor(0) 
RgbColor allColors[] = {Cblack, Cgreen, Corange, Cred,}; 
NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, PixelPin);

#pragma endregion

#pragma region ButtonSetUp

#define FLASH_BUTTON 0
int isTriggered= 0;
int agitationState =0;
RgbColor defaultNoiseStateColor =Cblack;
RgbColor noiseStateColor = defaultNoiseStateColor;

//timer
bool button_was_down = false;
unsigned long startTime = 0;
#pragma endregion

const uint8_t soundPin = A0;
double ambientSound = 0;
// number of listens before updating ambientSound
int const ambientSoundSpan = 200;
int positionInSpan = 0;
//Used for finding avarege level of sound in time span
double sumOfSound = 0;
double currentSoundLevel = 0;
//Work in progress !!!!
double soundActivationThreshold = 100;
void setup() {
  
  pinMode(FLASH_BUTTON,INPUT_PULLUP);

  pinMode(soundPin, INPUT);
  ambientSound = analogRead(soundPin);

  //sets up lightstrip
  strip.Begin();
  strip.Show();

  Serial.begin(115200L);
  
}

void loop() {
	ButtonIntensity();
	if(MonitorSound())
	{
	ButtonIntensity();
	Light();
	Serial.println("yup");
	strip.SetPixelColor(1, Cblack);
	strip.Show();
     
	}
	delay(250);
}


