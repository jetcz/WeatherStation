
#include <TimeAlarms.h>
#include <TimezoneESP8266.h>
#include <Time.h>
#include <MAX7219.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <PrivateData.h>



MAX7219 display(1, 15);  // Chips / CS



WiFiUDP udp;

unsigned int localPort = 2390;      // local port to listen for UDP packets
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
IPAddress NTPIP(195, 113, 144, 201);

byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
char buf[30];
WiFiClient client;
String time;
int timeAlarm;
bool synced = false;


TimeChangeRule CEST = { "CEST", Last, Sun, Mar, 2, 120 };    //summer time = UTC + 2 hours
TimeChangeRule CET = { "CET", Last, Sun, Oct, 3, 60 };		 //winter time = UTC + 1 hours
Timezone myTZ(CEST, CET);
TimeChangeRule *tcr;

void setup() {
	display.begin();
	time.reserve(50);
	udp.begin(localPort);

#pragma region net
	Serial.begin(115200);

	// We start by connecting to a WiFi network

	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	PrivateData p;
	Serial.println(p.SSID);

	WiFi.begin(p.SSID, p.Password);
	

	//String dots = "";
	//while (WiFi.status() != WL_CONNECTED) {
	//	delay(500);
	//	dots += '.';
	//	display.sendString(dots);
	//}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
#pragma endregion

	setSyncProvider(syncProvider); //sync system clock from RTC module
	setSyncInterval(10800);

	Alarm.timerRepeat(1, printLcd);

	if (!synced) timeAlarm = Alarm.timerRepeat(5, setTimeAlarm);
}


void loop() {
	yield();
	Alarm.delay(0);
}