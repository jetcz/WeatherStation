/// <summary>
/// Convert temperatre to string suitable for displaying on 4-digit lcd screen (last digit is "c")
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
inline char * tempToString(float val) {
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

/// <summary>
/// Convert float to string
/// </summary>
/// <param name="val">Value to convert</param>
/// <param name="len">Length of the resulting string (including decimal point)</param>
/// <param name="prec">How many decimals</param>
/// <returns></returns>
inline char * floatToString(float val, int len, int prec) {
	static char buf[6];
	dtostrf(val, len, prec, buf);  //1 is mininum width, 1 is precision; float value is copied onto buff
	return buf;
}
