#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "detabaseEsp8266.h"

// Replace with your actual project ID and base name
const char* detaKey = "a0uhqqxxxx_xxxxxxxxxxxxxxxxxxxxxxxx";
const char* detaID = "a0uhqqxxxxx";
const char* detaBaseName = "LOG";
const char* ssid = "SSID";
const char* password = "PASSWORD";

DetabaseEsp8266 detabase(detaKey, detaID, detaBaseName);

String entrykey = "123456";

void sendDetaSpace() {
  // Add data to the item
  detabase.addKey(entrykey);
  detabase.addData("stringValue", "merhaba");
  detabase.addData("intValue", 123);
  detabase.addData("floatValue", 123.123f); // Use the 'f' suffix to specify a float value
  detabase.addData("boolValue", true);

  // Send data and get the response payload
  String sentPayload = detabase.sendData();
  Serial.println("Data sent successfully. Payload:");
  Serial.println(sentPayload);
}

void GetDetaSpace() {
  // Retrieve and display the item
  String itemData = detabase.getItem(entrykey);
  Serial.println("Item Data:");
  Serial.println(itemData);

  // Access individual fields using the new functions
  String stringValue = detabase.getData("stringValue");
  int intValue = detabase.getIntData("intValue");
  float floatValue = detabase.getFloatData("floatValue");
  bool boolValue = detabase.getBoolData("boolValue");

  // Print the retrieved values
  Serial.print("stringValue: ");
  Serial.println(stringValue);
  Serial.print("intValue: ");
  Serial.println(intValue);
  Serial.print("floatValue: ");
  Serial.println(floatValue);
  Serial.print("boolValue: ");
  Serial.println(boolValue);
}

void deleteSpaceKey() {
  // Delete the item
  int deleteResponseCode = detabase.deleteItem(entrykey);
  if (deleteResponseCode == 200) {
    Serial.println("Item successfully deleted.");
  } else {
    Serial.println("Failed to delete item.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

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
  delay(5000);
  GetDetaSpace();
  delay(5000);
  deleteSpaceKey();
  delay(5000);
}