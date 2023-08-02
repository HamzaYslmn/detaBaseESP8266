#ifndef DETABASEESP8266_H
#define DETABASEESP8266_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

class DetabaseEsp8266 {
public:
  DetabaseEsp8266(const String& key, const String& id, const String& baseName);
  void addKey(const String& key);
  void addData(const String& field, const String& value);
  void addData(const String& field, int value);
  void addData(const String& field, float value);
  void addData(const String& field, bool value);
  void addData(const String& field, const char* value);
  String sendData();
  String getItem(const String& itemKey);
  int deleteItem(const String& itemKey);

  // Getter functions for different data types
  String getData(const String& field);
  int getIntData(const String& field);
  float getFloatData(const String& field);
  bool getBoolData(const String& field);

  // Helper function to print HTTP response code
  void printResponseCode(int code);

private:
  String detaKey;
  String detaID;
  String detaBaseName;
  DynamicJsonDocument doc;
  JsonObject dataObject;
  WiFiClientSecure client;
};

#endif // DETABASEESP8266_H
