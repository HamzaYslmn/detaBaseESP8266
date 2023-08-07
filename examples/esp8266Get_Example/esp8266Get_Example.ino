#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <detaBaseESP8266.h>
#include "certs.h"

const char* detaKey = "a0uhqqxxxx_xxxxxxxxxxxxxxxxxxxxxxxx";
const char* detaID = "a0uhqqxxxxx";
const char* detaBaseName = "LOG";
const char* ssid = "SSID";
const char* password = "PASSWORD";

detaBaseESP8266 detabase(detaKey, detaID, detaBaseName);

X509List cert(cert_DigiCert_Global_Root_CA);

void detaGet(){
    // Specify the key of the item you want to retrieve
  String itemKey = "item1";

  // Build the URL for the specific item
  String url = "https://database.deta.sh/v1/" + String(detaID) + "/" + String(detaBaseName) + "/items/" + String(itemKey);

  // Initialize the HTTP client and set headers
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", String(detaKey));

  // Send the GET request
  int httpResponseCode = http.GET();

  // Check the response code
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
    // Parse the JSON response if needed
    DynamicJsonDocument doc(256);
    deserializeJson(doc, response);
    Serial.println("Response: " + response);
    // Access data using doc["field1"] and doc["field2"]
    const char* field1Value = doc["field1"];
    const char* field2Value = doc["field2"];

    Serial.print("Field1: ");
    Serial.println(field1Value);
    Serial.print("Field2: ");
    Serial.println(field2Value);
    
  } else {
    Serial.println("Error on HTTP request");
  }

  http.end();
}

void setup() {
  Serial.begin(115200);

  configTime(3*3600, 0, "pool.ntp.org"); // For SSL, UTC+3 Turkey
  WiFiClientSecure client;
  client.setTrustAnchors(&cert);

  delay(100);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println("Connection Done");
}

void loop() {
  // Your code here
}