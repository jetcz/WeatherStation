
/// <summary>
/// Display sensor data and time on the lcd array
/// </summary>
void CreateDisplayString() {
	static bool dot = true;
	bool tarrifDot = FirstSync ? GetLowTariff() : false;
	LCDstr.theString = "";
	//line 1 dht in
	if (ds.isValid[0])
	{
		if (getTemperatureLengthOnLcd(ds.Data[0]) == 2)
		{
			LCDstr.theString += " ";
		}
		LCDstr.theString += u.ToString(ds.Data[0], true);
		LCDstr.theString += "c";

		LCDstr.theString += String(ds.Data[1], 0);
		if (getHumidityLengthOnLcd(ds.Data[1]) == 3)
		{
			LCDstr.theString += "h";
		}
		else LCDstr.theString += "rh";

		if (tarrifDot)
		{
			LCDstr.theString += ".";
		}
	}
	else LCDstr.theString += "dht err ";

	//line 2 dht out
	if (ds.isValid[1])
	{
		if (getTemperatureLengthOnLcd(ds.Data[3]) == 2)
		{
			LCDstr.theString += " ";
		}
		LCDstr.theString += u.ToString(ds.Data[3], true);
		LCDstr.theString += "c";

		LCDstr.theString += String(ds.Data[4], 0);
		if (getHumidityLengthOnLcd(ds.Data[4]) == 3)
		{
			LCDstr.theString += "h";
		}
		else LCDstr.theString += "rh";

		if (tarrifDot)
		{
			LCDstr.theString += ".";
		}
	}
	else LCDstr.theString += "dht err ";

	//line 3 time
	if (FirstSync)
	{
		time_t t = now();

		int h = (t % 86400L) / 3600;
		int m = (t % 3600) / 60;
		int s = (t % 60);

		if (h < 10)
		{
			LCDstr.theString += "0";
		}
		LCDstr.theString += h; // print the hour (86400 equals secs per day)
		LCDstr.theString += "-";
		if (m < 10) {
			// In the first 10 minutes of each hour, we'll want a leading '0'
			LCDstr.theString += "0";
		}
		LCDstr.theString += m; // print the minute (3600 equals secs per minute)
		LCDstr.theString += "-";
		if (dot)
		{
			LCDstr.theString += ".";
		}
		if (s < 10) {
			// In the first 10 seconds of each minute, we'll want a leading '0'
			LCDstr.theString += "0";
		}
		LCDstr.theString += s; // print the second

		if (tarrifDot)
		{
			LCDstr.theString += ".";
		}

		dot = !dot;
	}
	else LCDstr.theString += "ntp sync";

};

/// <summary>
/// called from interrupts
/// </summary>
void printLcd() {

	if (LCDstr.Ready)
	{
		display.sendString(LCDstr.theString);
		LCDstr.Ready = false;
	}
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
		lastVal = intensity;
	}

	//display.sendString("                        ");
	//display.sendString(String(intensity) + " " + String(counts));
}

int getTemperatureLengthOnLcd(double num) {

	long numrounded = round(num);
	if (numrounded >= (long)0.0)
	{
		if (numrounded >= (long)9.949)
		{
			return 3;
		}
		else
		{
			return 2;
		}

	}
	else
	{
		return 3;
	}
}

int getHumidityLengthOnLcd(double num)
{
	if (round(num) >= 100)
	{
		return 3;
	}
	else if (round(num) < 10)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
