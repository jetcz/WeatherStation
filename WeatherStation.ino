
#define DEBUG true

#include <Ticker.h>
#include <RunningAverage.h>
#include <dhtESP8266.h>
#include <TimeAlarms.h>
#include <TimezoneESP8266.h>
#include <Time.h>
#include <MAX7219.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <PrivateData.h>
#include <DataSet.h>
#include <SystemSettings.h>



const byte DHTInPin = 0;
const byte SPI_CS = 15;

MAX7219 display(2, SPI_CS);  // Chips / CS
WiFiUDP udp;
WiFiClient client;
DataSet ds;
SystemSettings Settings;
PrivateData pd;

Ticker lcdTicker;
TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };    //summer time = UTC + 2 hours
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };		 //winter time = UTC + 1 hours
Timezone myTZ(CEST, CET);
TimeChangeRule *tcr;
dhtESP8266 DHTIn;
dhtESP8266 DHTOut;

RunningAverage tempIn = RunningAverage(3);
RunningAverage tempOut = RunningAverage(3);
RunningAverage humIn = RunningAverage(3);
RunningAverage humOut = RunningAverage(3);
RunningAverage light = RunningAverage(3);


String lcdText;
int resyncAlarm;
bool synced = false;


void setup() {
	Serial.begin(115200);

	display.begin();
	display.setIntensity(5);

	lcdText.reserve(30);
	udp.begin(2390);

	WiFi.begin(pd.SSID, pd.Password);

	setSyncProvider(syncProvider); //sync system clock from ntp
	setSyncInterval(10800);

	ds.Latitude = Settings.Latitude;
	ds.Longitude = Settings.Longitude;

	//alarms
	lcdTicker.attach_ms(1000, printLcd); //print lcd using interrupt - it will always execute
	Alarm.timerRepeat(Settings.UpdateSensorsInterval, getSensors);
	Alarm.timerRepeat(Settings.UpdateThingSpeakInterval, updateThingSpeak);
	if (!synced) resyncAlarm = Alarm.timerRepeat(5, setTimeAlarm);

	//Alarm.timerRepeat(Settings.UpdateOpenWeatherMapInterval, updateOpenWeatherMap);

}


void loop() {
	yield();
	Alarm.delay(0);
}