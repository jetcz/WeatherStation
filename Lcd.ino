/// <summary>
/// Display sensor data and time on the lcd array
/// </summary>
void printLcd() {
	static bool dot = true;
	bool tarrifDot = FirstSync ? GetLowTariff() : false;
	LcdText = "";
	String s;
	//line 1 dht in
	if (ds.isValid[0])
	{
		s = u.ToString(ds.Data[0], true);
		if (s.length() == 3)
		{
			LcdText += " ";
		}
		LcdText += s;
		LcdText += "c";
		s = String(ds.Data[1], 0);
		LcdText += s;
		if (s.length() == 3)
		{
			LcdText += "h";
		}
		else LcdText += "rh";

		if (tarrifDot)
		{
			LcdText += ".";
		}
	}
	else LcdText += "dht err ";

	//line 2 dht out
	if (ds.isValid[1])
	{
		s = u.ToString(ds.Data[3], true);
		if (s.length() == 3)
		{
			LcdText += " ";
		}
		LcdText += s;
		LcdText += "c";
		s = String(ds.Data[4], 0);
		LcdText += s;
		if (s.length() == 3)
		{
			LcdText += "h";
		}
		else LcdText += "rh";

		if (tarrifDot)
		{
			LcdText += ".";
		}
	}
	else LcdText += "dht err ";

	//line 3 time
	if (FirstSync)
	{
		time_t t = now();

		int h = (t % 86400L) / 3600;
		int m = (t % 3600) / 60;
		int s = (t % 60);

		if (h < 10)
		{
			LcdText += "0";
		}
		LcdText += h; // print the hour (86400 equals secs per day)
		LcdText += "-";
		if (m < 10) {
			// In the first 10 minutes of each hour, we'll want a leading '0'
			LcdText += "0";
		}
		LcdText += m; // print the minute (3600 equals secs per minute)
		LcdText += "-";
		if (dot)
		{
			LcdText += ".";
		}
		if (s < 10) {
			// In the first 10 seconds of each minute, we'll want a leading '0'
			LcdText += "0";
		}
		LcdText += s; // print the second

		if (tarrifDot)
		{
			LcdText += ".";
		}

		dot = !dot;
	}
	else LcdText += "ntp sync";

	display.sendString(LcdText);
}


/// <summary>
/// Set backlight intensity based on analog reading of photoresistor
/// </summary>
void setBacklight() {
	static int lastVal;
	if (!Alarm.active(SetBacklightAlarm))
	{
		SetBacklightAlarm = Alarm.timerRepeat(1, setBacklight);
	}

	int counts = analogRead(17);
	light.addValue(counts);
	int intensity = round(pow(light.getAverage(), 1.9) * 4.0 / 100000.0);
	intensity = intensity > 15 ? 15 : intensity;

	if (intensity != lastVal)
	{
		display.setIntensity(intensity);
	}

	lastVal = intensity;

	//display.sendString("                        ");
	//display.sendString(String(intensity) + " " + String(counts));
}
