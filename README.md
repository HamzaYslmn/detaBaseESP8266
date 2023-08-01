# DetabaseEsp8266 Library

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
<img width="649" alt="image" src="https://github.com/HamzaYslmn/detaBaseArduinoESP8266/assets/78810304/1a4f9684-7c15-4a64-9853-c701b0a2f87b">

#Add Deta

```c
DetabaseEsp8266 detabase(detaKey, detaID, detaBaseName);
```
#Put Items
```c
void sendkeydetaspace(){
  // Add data to the item
  detabase.addKey("abcdefg"); //key = abcdefg       key.c_str()
  detabase.addData("field1", "merhaba");
  detabase.addData("kanser", "maba");
  detabase.addData("field3", "me");
  
  // Send data and get the response payload
  String sentPayload = detabase.sendData();
  Serial.println("Data sent successfully. Payload:");
  Serial.println(sentPayload);
}
```
#Get Item
```c
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
```
#Delete Item
```c
void deletekey(){
  // Delete the item
  int deleteResponseCode = detabase.deleteItem("abcdefg");
  if (deleteResponseCode == 200) {
    Serial.println("Item successfully deleted.");
  } else {
    Serial.println("Failed to delete item.");
  }
}
```
<img width="966" alt="image" src="https://github.com/HamzaYslmn/detaBaseArduinoESP8266/assets/78810304/4b9541d7-4251-47b5-ae90-4b2caa64158c">
