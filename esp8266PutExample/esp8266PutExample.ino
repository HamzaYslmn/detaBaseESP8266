#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>

// Replace with your actual project ID and base name
const char* detaKey = "a0uhqqxxxxx_xxxxxxxxxxxxxxxxxx";
const char* detaID = "a0uhqqxxxxx";
const char* detaBaseName = "LOG";
const char* ssid     = "SSID";
const char* password = "PASSWORD";

void setup() {
  Serial.begin(115200);
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

  // Build the URL for the base
  String url = "https://database.deta.sh/v1/" + String(detaID) + "/" + String(detaBaseName) + "/items";

  // Create a JSON buffer
  DynamicJsonDocument doc(256);

  // Create an array of items
  JsonArray items = doc.createNestedArray("items");

  // Create the first item and add it to the array
  JsonObject item1 = items.createNestedObject();
  item1["key"] = "item1";
  item1["field1"] = "value1";
  item1["field2"] = "value2";

  // Serialize the JSON payload to a string
  String payload;
  serializeJson(doc, payload);

  // Set the Content-Type header to application/json
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", String(detaKey));

  // Send the PUT request with the JSON payload
  int httpResponseCode = http.PUT(payload);

  // Check the response code
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
  } else {
    Serial.println("Error on HTTP request");
  }

  http.end();
}

void loop() {
  // Your code here
}
