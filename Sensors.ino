void getSensors() {

	int state = DHTIn.read22(DHTInPin);
	if (state == 0) {

		tempIn.addValue(DHTIn.temperature);
		humIn.addValue(DHTIn.humidity);

		ds.Data[0] = tempIn.getAverage();
		ds.Data[1] = humIn.getAverage();
		ds.Data[2] = getHumidex(DHTIn.temperature, DHTIn.humidity);
	}
	else
	{
		Serial.print("Reading failed: ");
		Serial.println(state);
	}


	ds.Data[7] = getUptime();

	ds.isValid = true;
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
