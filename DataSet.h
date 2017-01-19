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
		TimeStamp = 0;
		Size = 8;
		DataStr.reserve(120);
		this->u = u;
	}

	//fields
	volatile double Data[10] = { 0 };
	byte Size;
	bool isValid[2] = { false };
	time_t TimeStamp;
	String DataStr;

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
				DataStr += String(i + 1) + "=" + u.ToString(this->Data[i], false);
				if (i < this->Size - 1) DataStr += "&";
			}
		}
	}

}; typedef class DataSet DataSet;