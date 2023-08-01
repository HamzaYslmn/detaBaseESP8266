// detabaseEsp8266.cpp
#include "detabaseEsp8266.h"

DetabaseEsp8266::DetabaseEsp8266(const String& key, const String& id, const String& baseName)
    : detaKey(key), detaID(id), detaBaseName(baseName), doc(512) {
}

void DetabaseEsp8266::addKey(const String& key) {
  JsonObject item1 = doc["items"].createNestedObject();
  item1["key"] = key;
}

void DetabaseEsp8266::addData(const String& field, const String& value) {
  doc["items"][0][field] = value;
}

void DetabaseEsp8266::addData(const String& field, int value) {
  doc["items"][0][field] = value;
}

String DetabaseEsp8266::sendData() {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items";

  String payload;
  serializeJson(doc, payload);

  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", detaKey);

  int httpResponseCode = http.PUT(payload);
  String responsePayload = "";

  if (httpResponseCode > 0) {
    responsePayload = http.getString();
  }

  http.end();

  // Reset the DynamicJsonDocument after sending the data
  doc.clear();

  return responsePayload;
}

String DetabaseEsp8266::getItem(const String& itemKey) {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items/" + itemKey;

  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", detaKey);

  int httpResponseCode = http.GET();
  String responsePayload = "";

  if (httpResponseCode > 0) {
    responsePayload = http.getString();
  }

  http.end();

  return responsePayload;
}

int DetabaseEsp8266::deleteItem(const String& itemKey) {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items/" + itemKey;

  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", detaKey);

  int httpResponseCode = http.DELETE();

  http.end();

  return httpResponseCode;
}
