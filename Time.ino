/// <summary>
/// Get NTP time
/// </summary>
/// <returns></returns>
unsigned long ntp() {
	if (WiFi.status() != WL_CONNECTED) return 0;

	static const byte NTPPacketSize = 48; // NTP time stamp is in the first 48 bytes of the message
	static byte packetBuffer[NTPPacketSize]; //buffer to hold incoming and outgoing packets

	//send packet
	for (size_t i = 0; i < NTPPacketSize; i++)
	{
		packetBuffer[i] = 0;
	}
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
							 // 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	udp.beginPacket(Settings.NTPAddress, 123); //NTP requests are to port 123
	udp.write(packetBuffer, NTPPacketSize);
	udp.endPacket();

	//parse packet
	int cb = 0;
	int timeout = 0;
	do
	{
		Alarm.delay(3);
		timeout += 3;
		cb = udp.parsePacket();

	} while (!cb && timeout < 1000);


	if (cb == 0) {
#if DEBUG
		Serial.println(F("No NTP packet yet"));
#endif // DEBUG
		return 0;
	}
	else {
#if DEBUG
		Serial.println(F("Got NTP packet"));
#endif // DEBUG

		udp.read(packetBuffer, NTPPacketSize); // read the packet into the buffer
		unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
		unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = 0;
		if (timeout < 500)
		{
			epoch = secsSince1900 - seventyYears + 1;
		}
		else
		{
			epoch = secsSince1900 - seventyYears + 2;
		}
		return epoch;
	}
}

/// <summary>
/// Called repeatedly after bootup untile time is obtained from NTP
/// </summary>
void setTimeAlarm() {
	unsigned long time = ntp();
	if (time != 0)
	{
#if DEBUG
		Serial.println("NTP Sync " + (String)time);
#endif
		setTime(myTZ.toLocal(time, &tcr));

		if (!FirstSync)
		{
			Alarm.write(SyncAlarm, 10800);
			FirstSync = true;
		}
	}
	else {
#if DEBUG
		Serial.println("NTP Sync failed");
#endif
	}
}

/// <summary>
/// Get uptime
/// </summary>
/// <returns></returns>
unsigned long getUptime() {
	return 4294967 * millisRollover() + round(millis() / 1000);
}

/// <summary>
/// Exstension of classic millis(), handles overflow
/// </summary>
/// <returns></returns>
unsigned int millisRollover() {

	static unsigned int _nNumRollovers = 0; // variable that permanently holds the number of rollovers since startup
	static bool _bReadyToRoll = false; // tracks whether we've made it halfway to rollover
	unsigned long _lNow = millis(); // the time right now
	unsigned long _lHalfwayMillis = 2147483647; // this is halfway to the max millis value (17179868 for earlier versions of Arduino)

	if (_lNow > _lHalfwayMillis) { // as long as the value is greater than halfway to the max
		_bReadyToRoll = true; // you are ready to roll over
	}

	if (_bReadyToRoll == true && _lNow < _lHalfwayMillis) {
		// if we've previously made it to halfway
		// and the current millis() value is now _less_ than the halfway mark
		// then we have rolled over
		_nNumRollovers++; // add one to the count the number of rollovers
		_bReadyToRoll = false; // we're no longer past halfway
	}
	return _nNumRollovers;
}