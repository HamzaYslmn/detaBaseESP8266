#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <detabaseEsp8266.h>

// Replace with your actual project ID and base name
const char* detaKey = "a0uhqqxxxxx_xxxxxxxxxxxxxxxxxx";
const char* detaID = "a0uhqqxxxxx";
const char* detaBaseName = "LOG";
const char* ssid     = "SSID";
const char* password = "PASSWORD";

DetabaseEsp8266 detabase(detaKey, detaID, detaBaseName);

//---------------------------------------------------------------------------------------------------
void sendkeydetaspace(){
  // Add data to the item
  detabase.addKey("abcdefg");
  detabase.addData("field1", "merhaba");
  detabase.addData("kanser", "maba");
  detabase.addData("field3", "me");
  
  // Send data and get the response payload
  String sentPayload = detabase.sendData();
  Serial.println("Data sent successfully. Payload:");
  Serial.println(sentPayload);
}
//---------------------------------------------------------------------------------------------------
void GetKeyitem(){
  // Retrieve and display the item
  String itemData = detabase.getItem("abcdefg");
  Serial.println("Item Data:");
  printJsonData(itemData);
}
void printJsonData(const String& jsonString) {
  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, jsonString);

  if (error) {
    Serial.println("Failed to parse JSON data.");
    return;
  }

  // Access individual fields using doc["field_name"].as<Type>()
  String field1Value = doc["field1"];
  String kanserValue = doc["kanser"];
  String field3Value = doc["field3"];

  Serial.print("Field1: ");
  Serial.println(field1Value);
  Serial.print("Kanser: ");
  Serial.println(kanserValue);
  Serial.print("Field3: ");
  Serial.println(field3Value);
}
//---------------------------------------------------------------------------------------------------
void deletekey(){
  // Delete the item
  int deleteResponseCode = detabase.deleteItem("abcdefg");
  if (deleteResponseCode == 200) {
    Serial.println("Item successfully deleted.");
  } else {
    Serial.println("Failed to delete item.");
  }
}
//---------------------------------------------------------------------------------------------------
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

  // PUT data to the item
  sendkeydetaspace();

  // Retrieve and display the item
  GetKeyitem();

  delay(10000);
  // Delete the item
  deletekey();
}

void loop() {
  // Your code here
}