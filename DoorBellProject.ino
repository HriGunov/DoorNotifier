#include <FS.h>                   //this needs to be first, or it all crashes and burns...

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <ArduinoJson.h>		  //https://github.com/bblanchon/ArduinoJson

char device_name[50] = "json didn't work";
bool shouldSaveConfig = false;

void saveConfigCallback() {
	Serial.println("Should save config");
	shouldSaveConfig = true;
}

#pragma region NeoPixelSetUp


//RainbowStrip

#include <WiFiManager.h>
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

#pragma region SoundActivation


const uint8_t soundPin = A0;
double ambientSound = 0;
// number of listens before updating ambientSound
int const ambientSoundSpan = 200;
int positionInSpan = 0;
//Used for finding avarege level of sound in time span
double sumOfSound = 0;
double currentSoundLevel = 0;
//Work in progress !!!!
double soundActivationThreshold = 50;
#pragma endregion


void setup() {
  Serial.begin(115200L);

  pinMode(FLASH_BUTTON,INPUT_PULLUP);

  pinMode(soundPin, INPUT);
  ambientSound = analogRead(soundPin);

  //wifiManager
  if (SPIFFS.begin()) {
	  Serial.println("mounted file system");
	  if (SPIFFS.exists("/config.json")) {
		  //file exists, reading and loading
		  Serial.println("reading config file");
		  File configFile = SPIFFS.open("/config.json", "r");
		  if (configFile) {
			  Serial.println("opened config file");
			  size_t size = configFile.size();
			  // Allocate a buffer to store contents of the file.
			  std::unique_ptr<char[]> buf(new char[size]);

			  configFile.readBytes(buf.get(), size);
			  DynamicJsonBuffer jsonBuffer;
			  JsonObject& json = jsonBuffer.parseObject(buf.get());
			  json.printTo(Serial);
			  if (json.success()) {
				  Serial.println("\nparsed json");

				  strcpy(device_name, json["test"]);	 			  
			  }
			  else {
				  Serial.println("failed to load json config");
			  }
		  }
	  }	 
  }
  else {
	  Serial.println("failed to mount FS");
  }
  //end read

  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_device_name("server", "mqtt server", device_name, 40);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //Add custom parameters
  wifiManager.addParameter(&custom_device_name);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("ESP", "password")) {
	  Serial.println("failed to connect and hit timeout");
	  delay(3000);
	  //reset and try again, or maybe put it to deep sleep
	  ESP.reset();
	  delay(5000);
  }

  //updates local variables
  strcpy(device_name, custom_device_name.getValue());


  if (shouldSaveConfig) {
	  Serial.println("saving config");
	  DynamicJsonBuffer jsonBuffer;
	  JsonObject& json = jsonBuffer.createObject();
	  json["subnet"] = WiFi.subnetMask().toString();

	  File configFile = SPIFFS.open("/config.json", "w");
	  if (!configFile) {
		  Serial.println("failed to open config file for writing");
	  }

	  json.prettyPrintTo(Serial);
	  json.printTo(configFile);
	  configFile.close();
	  //end save
  }

  //sets up lightstrip
  strip.Begin();
  strip.Show();

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

//Debug function 
void Debug()
{
	if (SPIFFS.exists("/config.json")) {
		//file exists, reading and loading
		Serial.println("reading config file");
		File configFile = SPIFFS.open("/config.json", "r");
		if (configFile) {
			Serial.println("opened config file");
			size_t size = configFile.size();
			// Allocate a buffer to store contents of the file.
			std::unique_ptr<char[]> buf(new char[size]);

			configFile.readBytes(buf.get(), size);
			DynamicJsonBuffer jsonBuffer;
			JsonObject& json = jsonBuffer.parseObject(buf.get());
			json.printTo(Serial);
		}
	}
}
