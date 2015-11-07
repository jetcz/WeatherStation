
inline char * tempToString(float val) {
	int len = 4;
	int prec = 1;

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
