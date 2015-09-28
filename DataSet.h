
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
		TimeStamp = 0;
		Size = 8;
		isValid = true;
		ThingSpeakStr.reserve(70);
	}

	//properties
	float Data[8];
	byte Size; //size is used to determine length to the array. It is changed manulay in the code. Refer to alarms.ino
	bool isValid;
	String APIkey;
	time_t TimeStamp;
	String ThingSpeakStr;

	/// <summary>
	/// Create ThingSpeak string
	/// </summary>
	void GetTSString() {
		ThingSpeakStr = "";
		for (int i = 0; i < this->Size; i++)
		{
			if (this->Data[i] > -100) //in case we get some broken values which are -255
			{
				ThingSpeakStr += String(i + 1) + "=" + String(this->Data[i], 1);
				if (i < this->Size - 1) ThingSpeakStr += "&";
			}
		}
	}
}; typedef class DataSet DataSet;