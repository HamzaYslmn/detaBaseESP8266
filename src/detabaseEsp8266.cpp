#include "detabaseEsp8266.h"

DetabaseEsp8266::DetabaseEsp8266(const String& key, const String& id, const String& baseName)
    : detaKey(key), detaID(id), detaBaseName(baseName), doc(512), dataObject(doc.to<JsonObject>()) {
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

void DetabaseEsp8266::addData(const String& field, float value) {
  doc["items"][0][field] = value;
}

void DetabaseEsp8266::addData(const String& field, bool value) {
  doc["items"][0][field] = value;
}

void DetabaseEsp8266::addData(const String& field, const char* value) {
  doc["items"][0][field] = value;
}

String DetabaseEsp8266::sendData() {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items";

  String payload;
  serializeJson(doc, payload);

  client.setInsecure(); // Ignore SSL certificate verification (for testing only)

  HTTPClient http;
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", detaKey);

  int httpResponseCode = http.PUT(payload);
  lastResponseCode = httpResponseCode;

  String responsePayload = "";
  if (httpResponseCode > 0) {
    responsePayload = http.getString();
    updateDataObject(responsePayload);
    lastPayloadString = responsePayload; // Update lastPayloadString with the received payload
  }

  http.end();

  // Reset the DynamicJsonDocument after sending the data
  doc.clear();

  return responsePayload;
}

String DetabaseEsp8266::getItem(const String& itemKey) {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items/" + itemKey;

  HTTPClient http;
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", detaKey);

  int httpResponseCode = http.GET();
  lastResponseCode = httpResponseCode;

  String responsePayload = "";
  if (httpResponseCode > 0) {
    responsePayload = http.getString();
    updateDataObject(responsePayload);
    lastPayloadString = responsePayload; // Update lastPayloadString with the received payload
  }

  http.end();

  return responsePayload;
}

int DetabaseEsp8266::deleteItem(const String& itemKey) {
  String url = "https://database.deta.sh/v1/" + detaID + "/" + detaBaseName + "/items/" + itemKey;

  HTTPClient http;
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", detaKey);

  int httpResponseCode = http.DELETE();
  lastResponseCode = httpResponseCode;

  http.end();

  return httpResponseCode;
}

String DetabaseEsp8266::getData(const String& field) {
  if (dataObject.containsKey(field)) {
    return dataObject[field].as<String>();
  } else {
    return "";
  }
}

int DetabaseEsp8266::getIntData(const String& field) {
  if (dataObject.containsKey(field)) {
    return dataObject[field].as<int>();
  } else {
    return 0;
  }
}

float DetabaseEsp8266::getFloatData(const String& field) {
  if (dataObject.containsKey(field)) {
    return dataObject[field].as<float>();
  } else {
    return 0.0f;
  }
}

bool DetabaseEsp8266::getBoolData(const String& field) {
  if (dataObject.containsKey(field)) {
    return dataObject[field].as<bool>();
  } else {
    return false;
  }
}

int DetabaseEsp8266::lastResponse() const {
  return lastResponseCode;
}

String DetabaseEsp8266::lastPayload() const {
  return lastPayloadString;
}

void DetabaseEsp8266::updateDataObject(const String& payload) {
  deserializeJson(doc, payload);
  dataObject = doc.as<JsonObject>();
}
