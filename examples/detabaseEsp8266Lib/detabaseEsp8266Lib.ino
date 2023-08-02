#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "detabaseEsp8266.h"

const char* detaKey = "a0uhqqxxxx_xxxxxxxxxxxxxxxxxxxxxxxx";
const char* detaID = "a0uhqqxxxxx";
const char* detaBaseName = "LOG";
const char* ssid = "SSID";
const char* password = "PASSWORD";

String entryKey = "entrykey";

DetabaseEsp8266 detabase(detaKey, detaID, detaBaseName);

void setup() {
  Serial.begin(115200);
  configTime(10800, 0, "pool.ntp.org"); // For SSL, UTC+3 Turkey
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }
  Serial.println("Connection Done");
}

void loop() {
  // Your code here
  sendDetaSpace();
  delay(3000);
  GetDetaSpace();
  delay(3000);
  deleteSpaceKey();
  delay(3000);
}

// Example of PUT request
void sendDetaSpace() {
  detabase.addData("key", entryKey);
  detabase.addData("stringValue", "merhaba"); // string
  detabase.addData("intValue", 123);         // int
  detabase.addData("floatValue", 123.123f);  // Use the 'f' suffix to specify a float value
  detabase.addData("boolValue", true);       // boolean

  bool success = detabase.sendData(); // send

  Serial.print("HTTP Response code: ");
  Serial.println(detabase.lastResponseCode); // 200 OK
  Serial.println("Response Payload:");
  Serial.println(detabase.responsePayload); // Payload

  if (success) {
    Serial.println("Data added successfully!");
  } else {
    Serial.println("Failed to add data!");
  }
}

// Example of GET request
void GetDetaSpace() {
  detabase.getItem(entryKey); // get
  Serial.print("HTTP Response code: ");
  Serial.println(detabase.lastResponseCode);
  Serial.println("Response Payload:");
  Serial.println(detabase.responsePayload);

  String stringValue = detabase.getData("stringValue");
  int intValue = detabase.getIntData("intValue");
  float floatValue = detabase.getFloatData("floatValue");
  bool boolValue = detabase.getBoolData("boolValue");

  Serial.print("stringValue: ");
  Serial.println(stringValue);
  Serial.print("intValue: ");
  Serial.println(intValue);
  Serial.print("floatValue: ");
  Serial.println(floatValue);
  Serial.print("boolValue: ");
  Serial.println(boolValue);
}

// Example of DELETE request
void deleteSpaceKey() {
  bool isDeleted = detabase.deleteItem(entryKey);
  if (isDeleted) { // 200 OK
    Serial.println("Item deleted successfully");
  } else {
    Serial.println("Item deletion failed");
  }
}
