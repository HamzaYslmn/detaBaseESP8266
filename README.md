# [DetabaseEsp8266 Library](https://github.com/HamzaYslmn/detaBaseESP826)

![https://img.shields.io/github/downloads/HamzaYslmn/detaBaseESP8266/total.svg](https://img.shields.io/github/downloads/HamzaYslmn/detaBaseESP8266/total.svg)
![https://img.shields.io/github/release/HamzaYslmn/detaBaseESP8266.svg](https://img.shields.io/github/release/HamzaYslmn/detaBaseESP8266.svg)
![https://img.shields.io/github/stars/HamzaYslmn/detaBaseESP8266.svg?style=social&label=Star&maxAge=2592000](https://img.shields.io/github/stars/HamzaYslmn/detaBaseESP8266.svg?style=social&label=Star&maxAge=2592000)

## Introduction
Esp8266 library for more convenient use of deta.sh collections

## Required Items
To use this library, you'll need the following:

1. Deta Project ID
2. Deta Project Key (API Key)
3. Deta Base name

## Wifi Connection
Use 2.4Ghz Wifi

### Result Struct
<img width="1246" alt="image" src="https://github.com/HamzaYslmn/detaBaseESP8266/assets/78810304/130208c8-2317-4879-9156-c14384fb24bb">


#SSL 
```c
#include "certs.h"
X509List cert(cert_DigiCert_Global_Root_CA);

void setup() {
  configTime(3*3600, 0, "pool.ntp.org"); // For SSL, UTC+3 Turkey
  WiFiClientSecure client;
  client.setTrustAnchors(&cert);
}
```

#Add Deta
```c
DetabaseEsp8266 detabase(detaKey, detaID, detaBaseName);
```
#Put Items
```c
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
```
#Get Item
```c
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
```
#Delete Item
```c
void deleteSpaceKey() {
  bool isDeleted = detabase.deleteItem(entryKey);
  if (isDeleted) { // 200 OK
    Serial.println("Item deleted successfully");
  } else {
    Serial.println("Item deletion failed");
  }
}
```
#Update Item
```c
void UpdateDetaSpace() {
  detabase.UpdateSet("stringValue", "hehe");
  //detabase.UpdateSet("intValue", 15);
  //detabase.UpdateSet("floatValue", 3.14f); // f suffix for float
  detabase.UpdateSet("boolValue", false);
  
  detabase.UpdateIncrement("intValue", 2);
  detabase.UpdateIncrement("floatValue", 1.11f); // f suffix for float

  // Append example
  detabase.UpdateAppend("likes", "ramen"); // Needs to create the field first "likes"
  // Prepend example
  detabase.UpdatePrepend("likes", "pizza"); // Needs to create the field and add a value first "likes" and "pizza" 
  // Delete example
  detabase.UpdateDelete("purchases");  // Delete the whole field

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
```
<img width="968" alt="image" src="https://github.com/HamzaYslmn/detaBaseESP8266/assets/78810304/4ce0e525-5980-423c-b6c0-6c71752ae59f">

