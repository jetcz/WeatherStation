/// <summary>
/// Display sensor data and time on the lcd array
/// </summary>
void printLcd() {
	static bool dot = true;
	lcdText = "";
	String hum;
	//line 1 dht in
	if (ds.isValid[0])
	{
		lcdText += tempToString(ds.Data[0]);
		lcdText += "c";
		hum = floatToString(ds.Data[1], 2, 0);
		lcdText += hum;
		if (hum.length() == 3)
		{
			lcdText += "h";
		} else lcdText += "rh";
	}
	else lcdText += "dht err ";

	//line 2 dht out
	if (ds.isValid[1])
	{
		lcdText += tempToString(ds.Data[3]);
		lcdText += "c";
		hum = floatToString(ds.Data[4], 2, 0);
		lcdText += hum;
		if (hum.length() == 3)
		{
			lcdText += "h";
		}
		else lcdText += "rh";
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
	static int lastVal;
	if (!Alarm.active(SetBacklightAlarm))
	{
		SetBacklightAlarm = Alarm.timerRepeat(2, setBacklight);
	}

	int counts;
	int cnt = 0;
	do
	{
		if (cnt > 3)
		{
			return;
		}
		counts = analogRead(17);
		cnt++;
	} while (counts < 290 || counts > 328);

	counts = counts - 298;
	counts = counts < 0 ? 0 : counts;
	counts = counts > 30 ? 30 : counts;
	light.addValue(counts);
	int currentVal = int(light.getAverage() / 5.0);
	if (currentVal != lastVal)
	{
		display.setIntensity(currentVal);
	}
	lastVal = currentVal;

	//display.sendString("                        ");
	//display.sendString(String(intensity) + " " + String(counts));
}
