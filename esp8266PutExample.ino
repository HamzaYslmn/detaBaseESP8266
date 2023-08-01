#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>

void setup() {
  Serial.begin(115200);
  delay(100);

  // Replace with your actual project ID and base name
  const char* detaID = "a0uhqqqqqqy";
  const char* detaBaseName = "LOG";
  // Replace with your actual Data Key (X-API-Key)
  String api_key = "a0uhqqqqqqy_aSecretValue";

  // Build the URL for the base
  String url = "https://database.deta.sh/v1/" + String(detaID) + "/" + String(detaBaseName) + "/items";

  // Create a JSON buffer
  const size_t capacity = JSON_ARRAY_SIZE(2) + 2 * JSON_OBJECT_SIZE(3);
  DynamicJsonDocument doc(capacity);

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
  http.addHeader("X-API-Key", api_key);

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
