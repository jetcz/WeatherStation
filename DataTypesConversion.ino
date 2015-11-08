
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

inline char * floatToString(float val, int len, int prec) {
	static char buf[6];
	dtostrf(val, len, prec, buf);  //1 is mininum width, 1 is precision; float value is copied onto buff
	return buf;
}
