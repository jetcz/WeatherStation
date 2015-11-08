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
		DataStr.reserve(100);
	}

	//properties
	volatile double Data[10] = { 0 };
	byte Size;
	bool isValid[2] = { false };
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
			if ((this->isValid[0] && i < 3)
				|| (this->isValid[1] && (i >= 3 && i < 6))
				|| i >= 6)
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