
/// <summary>
/// Specific utils just for this weatherstation
/// </summary>
class Utils
{
public:
	String s;
	Utils()
	{
		s.reserve(6);
		s = "";
	}

	/// <summary>
	/// Convert double to string
	/// </summary>
	/// <param name="val">Value to convert</param>
	/// <param name="lcd">If true, adjust the number to print temperature to lcd<</param>
	/// <returns></returns>
	String ToString(double val, bool lcd) {

		if (!lcd)
		{
			if (val > 100) //uptime, light....
			{
				s = String(val, 0);
			}
			else { //temp, hum
				s = String(val, 2);
			}
		}
		else {
			if (val <= -10) //temp lcd
			{
				s = String(val, 0);
			}
			else {
				s = String(val, 1);
			}
		}

		//return (val > -1 && val < 0) ? "-" + str : str; //the sign 0 to -1 bug seems to be fixed 30.12.2015
		return s;
	}

}; typedef class Utils Utils;