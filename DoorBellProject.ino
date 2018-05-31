
//RainbowStrip

#include <NeoPixelBus.h>
const uint16_t PixelCount = 6; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 2;  // make sure to set this to the correct pin, ignored for Esp8266

#define Cred     RgbColor(255, 0, 0)
#define Cpink    RgbColor(255, 0, 128)
#define Clila    RgbColor(255, 0, 255)
#define Cviolet  RgbColor(128, 0, 255)
#define Cblue    RgbColor(0, 0, 255)
#define Cmblue   RgbColor(0, 128, 255)
#define Ccyan    RgbColor(0, 255, 255)
#define Cgreen   RgbColor(0, 255, 0)
#define Cyellow  RgbColor(255, 255, 0)
#define Corange  RgbColor(255, 100, 0)
#define Cwhite   RgbColor(255, 255, 255)
#define Cblack   RgbColor(0) 
RgbColor allColors[] = {Cblack, Cgreen, Corange, Cred,}; 
NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(PixelCount, PixelPin);
//RainbowStrip

#define FLASH_BUTTON 0
int isTriggered= 0;
int agitationState =0;
RgbColor defaultNoiseStateColor =Cblack;
RgbColor noiseStateColor = defaultNoiseStateColor;

//timer
bool button_was_down = false;
unsigned long startTime = 0;

void setup() {
  
  pinMode(FLASH_BUTTON,INPUT_PULLUP);

  //sets up lightstrip
  strip.Begin();
  strip.Show();

  Serial.begin(115200L);
    
}

void loop() {
  
  if(CheckTriggered())
  {
	ButtonIntensity();
	Light();
	Serial.println("yup");
	strip.SetPixelColor(1, Cblack);
	strip.Show();
     
  }
}

void DoaStuff()
{

  
}
