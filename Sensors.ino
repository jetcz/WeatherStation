void getSensors() {
	bool isValid = true;
	RunningAverage tempIn = RunningAverage(3);
	RunningAverage tempOut = RunningAverage(3);
	RunningAverage humIn = RunningAverage(3);
	RunningAverage humOut = RunningAverage(3);
	RunningAverage light = RunningAverage(3);


	int state = DHTIn.read22(DHTInPin);
	if (state == 0) {

		tempIn.addValue(DHTIn.temperature);
		humIn.addValue(DHTIn.humidity);

		ds.Data[0] = tempIn.getAverage();
		ds.Data[1] = humIn.getAverage();

		//Serial.print("Temp: ");
		//Serial.print(tempIn.getAverage());
		//Serial.println("C");
		//Serial.print("Hum:  ");
		//Serial.print(humIn.getAverage());
		//Serial.println("%RH");
		//Serial.println();

		isValid &= true;
	}
	else
	{
		Serial.print("Reading failed: ");
		Serial.println(state);
		isValid &= false;
	}


	ds.isValid = isValid;
}
