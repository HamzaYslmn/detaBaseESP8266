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
```
#Get Item
```c
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
```
#Delete Item
```c
void deleteSpaceKey() {
  // Delete the item
  int deleteResponseCode = detabase.deleteItem(entrykey);
  if (deleteResponseCode == 200) {
    Serial.println("Item successfully deleted.");
  } else {
    Serial.println("Failed to delete item.");
  }
}
```
<img width="966" alt="image" src="https://github.com/HamzaYslmn/detaBaseArduinoESP8266/assets/78810304/4b9541d7-4251-47b5-ae90-4b2caa64158c">
