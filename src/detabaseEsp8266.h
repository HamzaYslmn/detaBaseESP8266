#ifndef DETABASEESP8266_H
#define DETABASEESP8266_H

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class DetabaseEsp8266 {
public:
  DetabaseEsp8266(const char* apiKey = "", const char* projectId = "", const char* baseName = "", size_t capacity = 512);

  void addData(const char* key, const String& value);
  void addData(const char* key, const char* value);
  void addData(const char* key, int value);
  void addData(const char* key, float value);
  void addData(const char* key, bool value);

  bool sendData();
  void getItem(const String& key);
  bool deleteItem(const String& key);

  String getData(const char* key);
  int getIntData(const char* key);
  float getFloatData(const char* key);
  bool getBoolData(const char* key);

  int lastResponseCode;
  String responsePayload;

private:
  const char* apiKey;
  const char* projectId;
  const char* baseName;
  size_t capacity;

  DynamicJsonDocument doc;
};

#endif
