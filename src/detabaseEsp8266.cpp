#include "detabaseEsp8266.h"

DetabaseEsp8266::DetabaseEsp8266(const char* key, const char* id, const char* baseName)
    : detaKey(key), detaID(id), detaBaseName(baseName), doc(256) {
}

void DetabaseEsp8266::addKey(const char* key) {
  JsonObject item1 = doc["items"].createNestedObject();
  item1["key"] = key;
}

void DetabaseEsp8266::addData(const char* field, const char* value) {
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

  return responsePayload;
}

String DetabaseEsp8266::getItem(const char* itemKey) {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items/" + String(itemKey);

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

int DetabaseEsp8266::deleteItem(const char* itemKey) {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items/" + String(itemKey);

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
