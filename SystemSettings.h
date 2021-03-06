struct SystemSettings
{
	float TempInOffset = 0.5;
	float TempOutOffset = 0.7;
	const int InvalidValue = -255;
	const byte UpdateSensorsInterval = 15;
	const byte UpdateThingSpeakInterval = 60;
	const char* ThingSpeakAddress = "api.thingspeak.com";
	const char* NTPAddress = "tik.cesnet.cz";

}; typedef struct SystemSettings SystemSettings;