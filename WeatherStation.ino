
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


MAX7219 display(2, 15);  // Chips / CS
WiFiUDP udp;
WiFiClient client;
IPAddress NTPIP(195, 113, 144, 201);

TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };    //summer time = UTC + 2 hours
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };		 //winter time = UTC + 1 hours
Timezone myTZ(CEST, CET);
TimeChangeRule *tcr;

dhtESP8266 DHTIn;
const byte DHTInPin = 0;

DataSet ds;


String lcdText;
int timeAlarm;
bool synced = false;
int localPort = 2390;      // local port to listen for UDP packets

const byte NTPPacketSize = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTPPacketSize]; //buffer to hold incoming and outgoing packets
char buf[30];


void setup() {
	Serial.begin(115200);

	display.begin();
	display.setIntensity(10);

	lcdText.reserve(48);
	udp.begin(localPort);

	PrivateData pd;
	WiFi.begin(pd.SSID, pd.Password);
	ds.APIkey = pd.APIKey;
	ds.isValid = false;

	setSyncProvider(syncProvider); //sync system clock from RTC module
	setSyncInterval(10800);

	//alarms
	Alarm.timerRepeat(1, printLcd);
	Alarm.timerRepeat(10, getSensors);
	Alarm.timerRepeat(60, thingSpeak);
	if (!synced) timeAlarm = Alarm.timerRepeat(5, setTimeAlarm);


}


void loop() {
	yield();
	Alarm.delay(0);
}