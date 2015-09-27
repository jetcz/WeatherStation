unsigned long ntp() {

	sendNTPpacket(NTPIP);

	int cb = 0;
	int timeout = 0;
	do
	{
		delay(5);
		timeout += 5;
		cb = udp.parsePacket();

	} while (!cb && timeout < 1000);


	if (cb == 0) {
		Serial.println("no packet yet");
	}
	else {
		// We've received a packet, read the data from it
		udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

		unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
		unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;

		// now convert NTP time into everyday time:
		Serial.print("Unix time = ");
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears + timeout / 1000;
		// print Unix time:
		Serial.println(epoch);
		synced = true;
		return epoch;

	}
	return 0;
}


unsigned long sendNTPpacket(IPAddress& address)
{
	// set all bytes in the buffer to 0
	for (size_t i = 0; i < NTP_PACKET_SIZE; i++)
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
	udp.beginPacket(address, 123); //NTP requests are to port 123
	udp.write(packetBuffer, NTP_PACKET_SIZE);
	udp.endPacket();
}

void setTimeAlarm() {
	unsigned long time = ntp();
	if (time != 0)
	{
		setTime(myTZ.toLocal(time, &tcr));
		Alarm.disable(timeAlarm);
	}
}

String timeToString(time_t t) {

	static bool dot = true;

	time = "";
	int h = (t % 86400L) / 3600;
	int m = (t % 3600) / 60;
	int s = (t % 60);


	if (h < 10)
	{
		time += '0';
	}
	time += h; // print the hour (86400 equals secs per day)
	if (dot)
	{
		time += '.';
	}
	if (m < 10) {
		// In the first 10 minutes of each hour, we'll want a leading '0'
		time += '0';
	}
	time += m; // print the minute (3600 equals secs per minute)
	time += "  ";
	if (s < 10) {
		// In the first 10 seconds of each minute, we'll want a leading '0'
		time += '0';
	}
	time += s; // print the second

	dot = !dot;
	return time;
}

time_t syncProvider()
{
	return myTZ.toLocal(ntp(), &tcr);
}