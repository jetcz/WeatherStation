
/// <summary>
/// Specific utils just for this weatherstation
/// </summary>
class Utils
{
public:

/// <summary>
/// Convert float to string
/// THERE IS SOME BUG THAT VALUES FROM -1 TO 0 ARE CONVERTED TO STRING WITHOUT THE MINUS SIGN - THIS METHOD ADDS A HARDCODED MINUS TO THE STRING IF THE VALUE IS FROM -1 TO 0
/// </summary>
/// <param name="val">Value to convert</param>
/// <param name="len">Length of the resulting string (including decimal point)</param>
/// <param name="prec">How many decimals</param>
/// <returns></returns>
String floatToString(float val, int len, int prec) {
	static char buf[6];
	dtostrf(val, len, prec, buf);  //1 is mininum width, 1 is precision; float value is copied onto buff
	if (val < 0 && val > -1) buf[0] = char('-'); //this is really fucking horrible
	return buf;
}


/// <summary>
/// Convert temperatre to string suitable for displaying on 4-digit lcd screen (last digit is "c")
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
String tempToString(float val) {
	int len = 4;
	int prec = 1;

	//in case the temp is less than -10 we need one more place for the minus sign - do not print decimal place
	if (val < -10)
	{
		val = round(val);
		len = 3;
		prec = 0;
	}
	return floatToString(val, len, prec);
}

}; typedef class Utils Utils;