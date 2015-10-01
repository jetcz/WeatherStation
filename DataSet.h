
/// <summary>
/// Structure holding data from sensors sent to thingspeak
/// </summary>
class DataSet
{
public:
	/// <summary>
	/// constructor
	/// </summary>
	DataSet() {
		TimeStamp = Latitude = Longitude = 0;
		Size = 8;
		isValid = false;
		DataStr.reserve(100);
		for (int i = 0; i < this->Size; i++)
		{
			Data[i] = -255;
		}
	}

	//properties
	volatile double Data[10];
	byte Size; //size is used to determine length to the array. It is changed manulay in the code. Refer to alarms.ino
	bool isValid;
	time_t TimeStamp;
	String DataStr;
	float Latitude;
	float Longitude;

	/// <summary>
	/// Create ThingSpeak string
	/// </summary>
	void GetTSString() {
		DataStr = "";
		for (int i = 0; i < this->Size; i++)
		{
			if (this->Data[i] > -100) //in case we get some broken values which are -255
			{
				DataStr += String(i + 1) + "=" + String(this->Data[i], 2);
				if (i < this->Size - 1) DataStr += "&";
			}
		}
	}

	/// <summary>
	/// Create Open Weather Map string
	/// </summary>
	void GetOWMString() {
		DataStr = "";
		DataStr += "temp=";
		//DataStr += String(this->Data[3]);
		DataStr += String(this->Data[0], 1);
		DataStr += "&humidity=";
		//DataStr += String(this->Data[4]);
		DataStr += String(this->Data[1], 1);
		DataStr += "&lat=";
		DataStr += String(this->Latitude, 7);
		DataStr += "&long=";
		DataStr += String(this->Longitude, 7);
		DataStr += "&name=";
		DataStr += "WeatherStationNodeMCU";
	}
}; typedef class DataSet DataSet;