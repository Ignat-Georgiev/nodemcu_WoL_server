#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//TODO Fill in Wifi details
const char* ssid = *;
const char* password = *;

MDNSResponder mdns;
ESP8266WebServer server(80);
String webPage = "";

//TODO
// pins for PC control
int powerPin = *;
int resetPin = *;
int statusPin = *;
// Hint: Pins 2 and 16 have pull ups and can be used for power and reset

int state;



void setup()
{
  Serial.begin(115200);
  Serial.println();

  // set up web page
  webPage += "<h1>ESP8266 WoL Web Server</h1><p>Socket #1 <a href=\"on\"><button>on</button></a>&nbsp;<a href=\"off\"><button>off</button></a>&nbsp;<a href=\"power\"><button>toggle</button></a>&nbsp;<a href=\"reset\"><button>reset</button></a></p>";
  webPage += "<h4>PC Status: "+String(state)+"</h4>";


  pinMode(powerPin, INPUT);
  digitalWrite(powerPin, HIGH);
  pinMode(resetPin, INPUT);
  digitalWrite(resetPin, HIGH);
  pinMode(statusPin, INPUT);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  if (mdns.begin("esp8266", WiFi.localIP())) {
	  Serial.println("MDNS responder started");
  }


  // set up server handling
  server.on("/", []() {
	  server.send(200, "text/html", webPage);
  });
  server.on("/on", []() {
	  server.send(200, "text/html", webPage);
	  if (!isPowered) {
		  togglePin(powerPin, 400);
		  Serial.println("Powering on!!!");
		  delay(1000);
	  }
  });
  server.on("/off", []() {
	  server.send(200, "text/html", webPage);
	  if (isPowered) {
		  togglePin(powerPin, 400);
		  Serial.println("Powering off!!!");
		  delay(1000);
	  }
  });
  server.on("/power", []() {
	  server.send(200, "text/html", webPage);
	  togglePin(powerPin, 400);
	  Serial.println("Powering on!!!");
	  delay(1000);
  });
  server.on("/reset", []() {
	  server.send(200, "text/html", webPage);
	  togglePin(resetPin, 400);
	  Serial.println("Resetting!!!");
	  delay(1000);
  });

  server.begin();
  Serial.println("HTTP server started");
}


void loop(void) {
	server.handleClient();
  state = isPowered();
  webPage = "<h1>ESP8266 WoL Web Server</h1><p>Socket #1 <a href=\"on\"><button>on</button></a>&nbsp;<a href=\"off\"><button>off</button></a>&nbsp;<a href=\"power\"><button>toggle</button></a>&nbsp;<a href=\"reset\"><button>reset</button></a></p><h4>PC Status: "+String(state)+"</h4>";
}


void togglePin(int pin, int ms)
{
	digitalWrite(pin, LOW);
	pinMode(pin, OUTPUT);
	delay(ms);
	pinMode(pin, INPUT);
}

int isPowered() {
	return digitalRead(statusPin);
}


