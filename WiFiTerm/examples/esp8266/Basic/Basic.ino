#include <ESP8266WiFi.h>
const char* ssid = "";
const char* password = "";

#include "WiFiTerm.h"

ESP8266WebServer server(80);

void setup()
{
  Serial.begin(115200);
  Serial.print("\nConnecting to WIFI");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.begin();
  Serial.println("webServer started");

  term.begin(server);
  Serial.println("term started");
}

void loop()
{
  server.handleClient();
  term.handleClient();

  if (term.available())
  {
    term.print("Received : ");
    term.println(term.readString());
  }
}
