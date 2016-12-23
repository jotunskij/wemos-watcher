#include <DHT.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <AM2320.h>
#include "secrets.h"

#define DHTPIN D4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
AM2320 th;
 
const char* ssid = secrets::ssid;
const char* password = secrets::password;
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);

  Wire.begin();
 
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

  dht.begin();
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

   
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h)) {
    h = -1.0f;
  }

  if (isnan(t)) {
    t = -1.0f;
  }

  th.Read();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println(""); //  do not forget this one
  client.print("{humidity_d: '");
  client.print(h);
  client.print("', temp_d: '");
  client.print(t);
  client.print("', ");
  client.print("humidity_a: '");
  client.print(th.h);
  client.print("', temp_a: '");
  client.print(th.t);
  client.print("'}");
  
  delay(10);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
