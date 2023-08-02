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
<img width="1246" alt="image" src="https://github.com/HamzaYslmn/detaBaseESP8266/assets/78810304/130208c8-2317-4879-9156-c14384fb24bb">


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
  detabase.sendData();
  Serial.println(detabase.lastResponse()); // Print last response code
  Serial.println(detabase.lastPayload()); // Print last payload
}
```
#Get Item
```c
void GetDetaSpace() {
  // Retrieve and display the item
  detabase.getItem(entrykey);
  Serial.println(detabase.lastResponse()); // Print last response code
  Serial.println(detabase.lastPayload()); // Print last payload

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
  detabase.deleteItem(entrykey);
  Serial.println(detabase.lastResponse());
  if (detabase.lastResponse() == 200) {
    Serial.println("Item deleted successfully");
  }
  else {
    Serial.println("Item deletion failed");
  }
}
```
<img width="968" alt="image" src="https://github.com/HamzaYslmn/detaBaseESP8266/assets/78810304/4ce0e525-5980-423c-b6c0-6c71752ae59f">

