
/// <summary>
/// Specific utils just for this weatherstation
/// </summary>
class Utils
{
public:

	/// <summary>
	/// Convert double to string
	/// THERE IS SOME BUG THAT VALUES FROM -1 TO 0 ARE CONVERTED TO STRING WITHOUT THE MINUS SIGN - THIS METHOD ADDS A HARDCODED MINUS TO THE STRING IF THE VALUE IS FROM -1 TO 0
	/// </summary>
	/// <param name="val">Value to convert</param>
	/// <param name="lcd">If true, adjust the number to print temperature to lcd<</param>
	/// <returns></returns>
	String ToString(double val, bool lcd) {
		String str;
		if (!lcd)
		{
			if (val > 100) //uptime, light....
			{
				str = String(val, 0);
			}
			else { //temp, hum
				str = String(val, 2);
			}
		}
		else {
			if (val < -10) //temp lcd
			{
				str = String(val, 0);
			}
			else {
				str = String(val, 1);
			}
		}

		return (val > -1 && val < 0) ? "-" + str : str;
	}

}; typedef class Utils Utils;