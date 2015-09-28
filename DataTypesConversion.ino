
char * floatToString(float val) {
	dtostrf(val, 3, 1, buf);  //1 is mininum width, 1 is precision; float value is copied onto buff
	return buf;

}
