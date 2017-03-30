#define DEBUG false

#include <Ticker.h>
#include <RunningAverage.h>
#include <dhtESP8266.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <TimezoneESP8266.h>
#include <MAX7219.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//custom structs
#include "Utils.h"
#include "PrivateData.h"
#include "DataSet.h"
#include "SystemSettings.h"
#include "TariffSettings.h"
#include "LCDString.h"

//pin mapping - subtract 1 from D???
//D0 = 16;
//D1 = 5;
//D2 = 4;
//D3 = 0;
//D4 = 2;
//D5 = 14;
//D6 = 12;
//D7 = 13;
//D8 = 15;
//D9 = 3;
//D10 = 1;

const byte DHTInPin = 0;
const byte DHTOutPin = 4;
const byte SPI_CS = 15;

MAX7219 display(3, SPI_CS);  // Chips / CS
WiFiUDP udp;
WiFiClient client;
Utils u;
DataSet ds(u);
SystemSettings Settings;
PrivateData pd;
Ticker lcdTicker;
TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };    //summer time = UTC + 2 hours
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };		 //winter time = UTC + 1 hours
Timezone myTZ(CEST, CET);
TimeChangeRule *tcr;
dhtESP8266 DHT;
LCDString LCDstr;
RunningAverage tempIn = RunningAverage(3);
RunningAverage tempOut = RunningAverage(3);
RunningAverage humIn = RunningAverage(3);
RunningAverage humOut = RunningAverage(3);
RunningAverage light = RunningAverage(5);

int SyncAlarm;
int SetBacklightAlarm;
bool FirstSync = false;
Tariff tariff;

void setup() {
#if DEBUG
	Serial.begin(115200); //serial console is very unreliable for some reason
#endif // DEBUG

	display.begin();
	display.setIntensity(0);

	WiFi.begin(pd.SSID, pd.Password);

	udp.begin(2390);

	//alarms
	lcdTicker.attach_ms(1000, printLcd); //print lcd using interrupt - it will always execute
	Alarm.timerOnce(3, setBacklight);
	Alarm.timerRepeat(Settings.UpdateSensorsInterval, getSensors);
	Alarm.timerRepeat(Settings.UpdateThingSpeakInterval, updateThingSpeak);
	SyncAlarm = Alarm.timerRepeat(5, setTimeAlarm);
}

void loop() {
	yield();
	Alarm.delay(0);
	if (!LCDstr.Ready)
	{
		CreateDisplayString();
		LCDstr.Ready = true;
	}
}
