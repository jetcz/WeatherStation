struct SystemSettings
{
	float TempInOffset = 0.8;

	const int InvalidValue = -255;
	const byte UpdateSensorsInterval = 10;
	const byte UpdateThingSpeakInterval = 60;
	const int UpdateOpenWeatherMapInterval = 1800;
	const char* ThingSpeakAddress = "api.thingspeak.com";
	const char* OpenWeatherMapAddress = "openweathermap.org";
	const char* NTPAddress = "tik.cesnet.cz";
	float Latitude = 50.2001119;
	float Longitude = 15.8426169;


}; typedef struct SystemSettings SystemSettings;