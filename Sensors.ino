/// <summary>
/// Read sensor data and prepare dataset
/// </summary>
void getSensors() {
	//inside
	if (DHT.read22(DHTInPin) == 0) {

		tempIn.addValue(DHT.temperature + Settings.TempInOffset);
		humIn.addValue(DHT.humidity);
		ds.Data[0] = tempIn.getAverage();
		ds.Data[1] = humIn.getAverage();
		ds.Data[2] = getHumidex(DHT.temperature, DHT.humidity);
		ds.isValid[0] = true;
	}
	else
	{
#if DEBUG
		Serial.print("Reading failed: ");
		Serial.println(state);
#endif // DEBUG
		ds.isValid[0] = false;
	}
	//outside
	if (DHT.read22(DHTOutPin) == 0) {
		tempOut.addValue(DHT.temperature + Settings.TempOutOffset);
		humOut.addValue(DHT.humidity);
		ds.Data[3] = tempOut.getAverage();
		ds.Data[4] = humOut.getAverage();
		ds.Data[5] = getHumidex(DHT.temperature, DHT.humidity);
		ds.isValid[1] = true;
	}
	else
	{
#if DEBUG
		Serial.print("Reading failed: ");
		Serial.println(state);
#endif // DEBUG
		ds.isValid[1] = false;
	}

	ds.Data[6] = light.getAverage();
	ds.Data[7] = getUptime();
	}


/// <summary>
/// Calculate humidex
/// To use pow() function refer to https://github.com/esp8266/Arduino/issues/612
/// </summary>
/// <param name="temp">Temperature</param>
/// <param name="hum">Humidity </param>
/// <returns></returns>
float getHumidex(float temp, float hum) {
	float e = (6.112 * pow(10, (7.5 * temp / (237.7 + temp))) *  hum / 100.0); //vapor pressure
	float humidex = temp + 0.55555555 * (e - 10.0); //humidex
	return humidex;
}
