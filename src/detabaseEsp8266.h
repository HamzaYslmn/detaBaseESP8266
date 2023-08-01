#ifndef DETABASEESP8266_H
#define DETABASEESP8266_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class DetabaseEsp8266 {
public:
  DetabaseEsp8266(const char* key, const char* id, const char* baseName);
  void addKey(const char* key);
  void addData(const char* field, const char* value);
  String sendData();
  String getItem(const char* itemKey);
  int deleteItem(const char* itemKey);

private:
  String detaKey;
  String detaID;
  String detaBaseName;
  DynamicJsonDocument doc;
};

#endif // DETABASEESP8266_H
