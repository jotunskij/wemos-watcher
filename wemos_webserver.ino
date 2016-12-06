/*
 * To setup environment:
 * Install https://www.wemos.cc/downloads
 * Install Python/pip
 * Create the directory [sketchbook directory]/hardware/esp8266com
 * Run the following commands in that directory:
 * %> git clone https://github.com/esp8266/Arduino.git esp8266
 * %> cd esp8266/tools
 * %> python get.py
 *
 * To setup Arduino IDE:
 * Set board to "WeMos D1 R2 & mini"
 * CPU frequency: 80 Mhz
 * Flash size: 4M (1M ..)
 * Upload speed: 115200
 * Port: /dev/cu.wchusbserial1420
 * Programmer: AVRISP mkII
 * 
 * Set serial monitor to:
 * 115200 baud
 * 
 */

#include <ESP8266WiFi.h>
#include "secrets.h"
 
const char* ssid = secrets::ssid;
const char* password = secrets::password;
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("New client connected");
  while(!client.available()){
    delay(10);
  }
 
  // Read the first line of the request
  //String request = client.readStringUntil('\r');
  //Serial.println(request);
  //client.flush();
 
  // Match the request
 
  /*int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }*/

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println(""); //  do not forget this one
  client.println("{temp: '25', humidity: '65'}");
 
  delay(10);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
