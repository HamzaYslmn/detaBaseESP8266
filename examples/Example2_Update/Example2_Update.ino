#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <detabaseEsp8266.h>
#include "certs.h"

const char* detaKey = "a0uhqqxxxx_xxxxxxxxxxxxxxxxxxxxxxxx";
const char* detaID = "a0uhqqxxxxx";
const char* detaBaseName = "LOG";
const char* ssid = "SSID";
const char* password = "PASSWORD";

String entryKey = "000MERHABA";

DetabaseEsp8266 detabase(detaKey, detaID, detaBaseName);

X509List cert(cert_DigiCert_Global_Root_CA);

bool onboardled;
int integer = 0;

// Example of PUT request
void sendDetaSpace() {
  detabase.addData("key", entryKey);
  detabase.addData("stringValue", "merhaba"); // string
  detabase.addData("intValue", integer);         // int
  detabase.addData("floatValue", 123.123f);  // Use the 'f' suffix to specify a float value
  detabase.addData("boolValue", true);       // boolean
  detabase.addData("0Led State", true);

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

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // Onboard LED OFF

  configTime(3*3600, 0, "pool.ntp.org"); // For SSL, UTC+3 Turkey
  WiFiClientSecure client;
  client.setTrustAnchors(&cert);

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

  //Send First Customizations
  sendDetaSpace();
}

void loop() {
  GetDetaSpace();
  delay(5000);
  UpdateDetaSpace();
  delay(15000);
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

  // Led State Control
  onboardled = detabase.getBoolData("0Led State");
  Serial.println("Led State: ");
  Serial.println(onboardled);
  if (onboardled) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Led ON");
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Led OFF");
  }
}

void UpdateDetaSpace() {
  detabase.UpdateSet("stringValue", "hehe");
  //detabase.UpdateSet("intValue", 15);
  //detabase.UpdateSet("floatValue", 3.14f); // f suffix for float
  detabase.UpdateSet("boolValue", false);
  
  detabase.UpdateIncrement("intValue", 2);
  detabase.UpdateIncrement("floatValue", 1.11f); // f suffix for float

  // Append example
  //detabase.UpdateAppend("likes", "ramen"); // Needs to create the field first "likes"
  // Prepend example
  //detabase.UpdatePrepend("likes", "pizza"); // Needs to create the field and add a value first "likes" and "pizza" 
  // Delete example
  //detabase.UpdateDelete("purchases");  // Delete the whole field

  // Call detabase.sendUpdate() to send the updates to the database
  bool success = detabase.sendUpdate(entryKey); // send

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