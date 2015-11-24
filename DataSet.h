/// <summary>
/// Structure holding data from sensors sent to thingspeak
/// </summary>
class DataSet
{
private:
	Utils u;

public:
	/// <summary>
	/// constructor
	/// </summary>
	DataSet(Utils u) {
		TimeStamp = Latitude = Longitude = 0;
		Size = 8;
		DataStr.reserve(100);
		this->u = u;
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
				DataStr += String(i + 1) + "=" + u.floatToString(this->Data[i], 3, 2);
				if (i < this->Size - 1) DataStr += "&";
			}
		}
	}

}; typedef class DataSet DataSet;