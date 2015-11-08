/// <summary>
/// Display sensor data and time on the lcd array
/// </summary>
void printLcd() {
	static bool dot = true;
	lcdText = "";

	//line 1 dht in
	if (ds.isValid[0])
	{
		lcdText += tempToString(ds.Data[0]);
		lcdText += "c";
		lcdText += floatToString(ds.Data[1], 2, 0);
		lcdText += "rh";
	}
	else lcdText += "dht err ";

	//line 2 dht out
	if (ds.isValid[1])
	{
		lcdText += tempToString(ds.Data[3]);
		lcdText += "c";
		lcdText += floatToString(ds.Data[4], 2, 0);
		lcdText += "rh";
	}
	else lcdText += "dht err ";

	//line 3 time
	if (synced)
	{
		time_t t = now();

		int h = (t % 86400L) / 3600;
		int m = (t % 3600) / 60;
		int s = (t % 60);

		if (h < 10)
		{
			lcdText += "0";
		}
		lcdText += h; // print the hour (86400 equals secs per day)
		lcdText += "-";
		if (m < 10) {
			// In the first 10 minutes of each hour, we'll want a leading '0'
			lcdText += "0";
		}
		lcdText += m; // print the minute (3600 equals secs per minute)
		lcdText += "-";
		if (dot)
		{
			lcdText += ".";
		}
		if (s < 10) {
			// In the first 10 seconds of each minute, we'll want a leading '0'
			lcdText += "0";
		}
		lcdText += s; // print the second

		dot = !dot;
	}
	else lcdText += "ntp sync";

	display.sendString(lcdText);
}

/// <summary>
/// Set backlight intensity based on analog reading of photoresistor
/// (wiring is weird and it gives readings from 290 to 328 but fuck it)
/// </summary>
void setBacklight() {
	int counts;
	do
	{
		counts = analogRead(A0);
	} while (counts < 290 || counts > 328);

	counts = counts - 298;
	counts = counts < 0 ? 0 : counts;
	counts = counts > 30 ? 30 : counts;
	light.addValue(counts);
	display.setIntensity(int(light.getAverage() / 5.0));

	//display.sendString("                        ");
	//display.sendString(String(intensity) + " " + String(counts));
}
