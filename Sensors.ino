void getSensors() {
	int state;
	static bool sensor = true;
	if (sensor)
	{
		state = DHTIn.read22(DHTInPin);
		if (state == 0) {

			tempIn.addValue(DHTIn.temperature + Settings.TempInOffset);
			humIn.addValue(DHTIn.humidity);

			ds.Data[0] = tempIn.getAverage();
			ds.Data[1] = humIn.getAverage();
			ds.Data[2] = getHumidex(DHTIn.temperature, DHTIn.humidity);

			ds.isValid[0] = true;
		}
		else
		{
			Serial.print("Reading failed: ");
			Serial.println(state);
			ds.isValid[0] = false;
		}
	}
	else 
	{
		state = DHTOut.read22(DHTOutPin);
		if (state == 0) {

			tempOut.addValue(DHTOut.temperature + Settings.TempOutOffset);
			humOut.addValue(DHTOut.humidity);

			ds.Data[3] = tempOut.getAverage();
			ds.Data[4] = humOut.getAverage();
			ds.Data[5] = getHumidex(DHTOut.temperature, DHTOut.humidity);

			ds.isValid[1] = true;
		}
		else
		{
			Serial.print("Reading failed: ");
			Serial.println(state);
			ds.isValid[1] = false;
		}
	}

	sensor = !sensor;
	ds.Data[7] = getUptime();
}

float getHumidex(float temp, float hum) {
	float e = (6.112 * pow(10, (7.5 * temp / (237.7 + temp))) *  hum / 100.0); //vapor pressure
	float humidex = temp + 0.55555555 * (e - 10.0); //humidex
	return humidex;
}



//for some reason math.h doesnt work
inline double pow(double x, double y)
{
	double z, p = 1;
	//y<0 ? z=-y : z=y ;
	if (y < 0)
		z = fabs(y);
	else
		z = y;
	for (int i = 0; i < z; ++i)
	{
		p *= x;
	}
	if (y < 0)
		return 1 / p;
	else
		return p;
}

inline double fabs(double x)
{
	return(x < 0 ? -x : x);
}
