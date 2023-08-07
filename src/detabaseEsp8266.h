#ifndef DETABASEESP8266_H
#define DETABASEESP8266_H

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

class DetabaseEsp8266 {
public:
  DetabaseEsp8266(const char* apiKey = "", const char* projectId = "", const char* baseName = "", size_t capacity = 512);

  //PUT
  void addData(const char* key, const String& value);
  void addData(const char* key, const char* value);
  void addData(const char* key, int value);
  void addData(const char* key, float value);
  void addData(const char* key, bool value);
  bool sendData();

  //GET
  void getItem(const String& key);
  String getData(const char* key);
  int getIntData(const char* key);
  float getFloatData(const char* key);
  bool getBoolData(const char* key);

  //DELETE
  bool deleteItem(const String& key);
  
  //UPDATE
  void UpdateSet(const char* key, const String& value);
  void UpdateSet(const char* key, const char* value);
  void UpdateSet(const char* key, int value);
  void UpdateSet(const char* key, float value);
  void UpdateSet(const char* key, bool value);

  void UpdateIncrement(const char* key, int value);
  void UpdateIncrement(const char* key, float value);

  void UpdateAppend(const char* key, const String& value);
  void UpdateAppend(const char* key, const char* value);

  void UpdatePrepend(const char* key, const String& value);
  void UpdatePrepend(const char* key, const char* value);

  void UpdateDelete(const char* key);

  bool sendUpdate(const String& key);

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
