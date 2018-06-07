
void SendActivation()
{
	Serial.println("Activation");
	if ((WiFi.status() == WL_CONNECTED)) {

		HTTPClient http;
		// configure traged server and url
		String url = "http://api.thingspeak.com/update?api_key=HU97PU6V6DSEO1DI&field1=";
		url += String(device_name);
		url += "&field2=";
		url += Time();

		
		//http.begin("http://192.168.1.12/test.html"
		http.begin(url); //HTTP


		int httpCode = http.GET();

		// httpCode will be negative on error
		if (httpCode > 0) {
			// HTTP header has been send and Server response header has been handled
			Serial.printf("[HTTP] GET... code: %d\n", httpCode);

			// file found at server
			if (httpCode == HTTP_CODE_OK) {
				String payload = http.getString();
				Serial.println(payload);
			}
		}
		else {
			Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
		}

		http.end();
	}
}

String Time()
{
	time_t now = time(nullptr);
	Serial.println(ctime(&now));
	
	return String(ctime(&now));
}