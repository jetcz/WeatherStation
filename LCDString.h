
/// <summary>
/// provides mechanism to construct displayed string on the lcd
/// </summary>
class LCDString {
public:
	String theString;
	volatile bool Ready;

	LCDString()
	{
		theString.reserve(128);
		Ready = false;
	}
}; typedef class LCDString LCDString;
