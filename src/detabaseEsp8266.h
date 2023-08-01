// detabaseEsp8266.h
#ifndef DETABASEESP8266_H
#define DETABASEESP8266_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class DetabaseEsp8266 {
public:
  DetabaseEsp8266(const String& key = "", const String& id = "", const String& baseName = "");
  void addKey(const String& key);
  void addData(const String& field, const String& value); // Overloaded function for String data
  void addData(const String& field, int value); // Overloaded function for int data
  String sendData();
  String getItem(const String& itemKey);
  int deleteItem(const String& itemKey);

private:
  String detaKey;
  String detaID;
  String detaBaseName;
  DynamicJsonDocument doc;
};

#endif // DETABASEESP8266_H
