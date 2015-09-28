/// <summary>
/// Helper method to call Thingspeak upload, rotate datasets and restart arduino if there problems uploading
/// </summary>
void thingSpeak() {
	if (WiFi.status() != WL_CONNECTED || !ds.isValid) return;

	ds.GetTSString();

#if DEBUG
	Serial.println();
	Serial.println(F("Updating ThingSpeak"));
#endif
	updateThingSpeak();
}


/// <summary>
/// Upload ThingSpeak data
/// </summary>
void updateThingSpeak() {

	client.flush();
	//connect to thingspeak
	unsigned static long _lLastCnn;
	if (!client.connected() || now() - _lLastCnn > 420) //for some reason the connection doesn't last past 500 sec, so we need to close and reopen it manualy for maximum reliability
	{
		client.stop();
#if DEBUG
		Serial.print(F("Connecting to ThingSpeak..."));
#endif		

		if (client.connect(Settings.ThingSpeakAddress, 80)) _lLastCnn = now();

	}
	//update thingspeak
	if (client.connected()) {

#if DEBUG
		Serial.println(F("Connected to ThingSpeak, sending data..."));
		Serial.println(ds.ThingSpeakStr);
#endif
		//why the hell the post doesnt work
		//client.print(F("POST /update HTTP/1.1\n"));
		//client.print(F("Host: api.thingspeak.com\n"));
		//client.print(F("Connection: Keep-Alive\n"));
		//client.print(F("X-THINGSPEAKAPIKEY: "));
		//client.print(ds.APIkey + "\n");
		//client.print(F("headers: false\n"));
		//client.print(F("Content-Type: application/x-www-form-urlencoded\n"));
		//client.print(F("Content-Length: "));
		//client.print(ds.ThingSpeakStr.length() + "\n\n");
		//client.println(ds.ThingSpeakStr);

		client.print(F("GET /update?key="));
		client.print(ds.APIkey);
		client.print(F("&"));
		client.print(ds.ThingSpeakStr);
		client.print(F(" HTTP/1.1\r\n"));
		client.print(F("Host: api.thingspeak.com\r\n"));
		client.print(F("Accept: */*\r\n"));
		client.print(F("headers: false\r\n"));
		client.print(F("\r\n"));
	}
	else
	{
		client.stop();
#if DEBUG
		Serial.println(F("Connecting to ThingSpeak failed"));

#endif
	}
}
