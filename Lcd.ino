void printLcd() {
	static bool dot = true;
	lcdText = "";
	//line 2 dht in
	if (ds.Data[0] && ds.Data[1])
	{
		lcdText += floatToString(ds.Data[0]);
		lcdText += "c";
		lcdText += (int)(ds.Data[1]);
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
		lcdText += ".";
		if (m < 10) {
			// In the first 10 minutes of each hour, we'll want a leading '0'
			lcdText += "0";
		}
		lcdText += m; // print the minute (3600 equals secs per minute)
		lcdText += "  ";
		if (s < 10) {
			// In the first 10 seconds of each minute, we'll want a leading '0'
			lcdText += "0";
		}
		lcdText += s; // print the second
		if (dot)
		{
			lcdText += ".";
		}
		dot = !dot;
	}
	else lcdText += "ntp sync";

	display.sendString(lcdText);
}


