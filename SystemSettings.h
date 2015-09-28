struct SystemSettings
{
	const int InvalidValue = -255;
	const byte UpdateSensorsInterval = 10;
	const byte UpdateThingSpeakInterval = 60;
	const char* ThingSpeakAddress = "api.thingspeak.com";
	const char* NTPAddress = "tik.cesnet.cz";

}; typedef struct SystemSettings SystemSettings;