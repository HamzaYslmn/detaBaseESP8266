#include "detaBaseESP8266.h"

detaBaseESP8266::detaBaseESP8266(const char* apiKey, const char* projectId, const char* baseName, size_t capacity)
  : apiKey(apiKey), projectId(projectId), baseName(baseName), capacity(capacity), doc(capacity) {}

void detaBaseESP8266::addData(const char* key, const String& value) {
  doc["items"][0][key] = value;
}

void detaBaseESP8266::addData(const char* key, const char* value) {
  doc["items"][0][key] = value;
}

void detaBaseESP8266::addData(const char* key, int value) {
  doc["items"][0][key] = value;
}

void detaBaseESP8266::addData(const char* key, float value) {
  doc["items"][0][key] = value;
}

void detaBaseESP8266::addData(const char* key, bool value) {
  doc["items"][0][key] = value;
}

void detaBaseESP8266::UpdateSet(const char* key, const String& value) {
  doc["set"][key] = value;
}

void detaBaseESP8266::UpdateSet(const char* key, const char* value) {
  doc["set"][key] = value;
}

void detaBaseESP8266::UpdateSet(const char* key, int value) {
  doc["set"][key] = value;
}

void detaBaseESP8266::UpdateSet(const char* key, float value) {
  doc["set"][key] = value;
}

void detaBaseESP8266::UpdateSet(const char* key, bool value) {
  doc["set"][key] = value;
}

void detaBaseESP8266::UpdateIncrement(const char* key, int value) {
  doc["increment"][key] = value;
}

void detaBaseESP8266::UpdateIncrement(const char* key, float value) {
  doc["increment"][key] = value;
}

void detaBaseESP8266::UpdateAppend(const char* key, const String& value) {
  JsonArray arr = doc["append"][key].to<JsonArray>();
  arr.add(value);
}

void detaBaseESP8266::UpdateAppend(const char* key, const char* value) {
  JsonArray arr = doc["append"][key].to<JsonArray>();
  arr.add(value);
}

void detaBaseESP8266::UpdatePrepend(const char* key, const String& value) {
  JsonArray arr = doc["prepend"][key].to<JsonArray>();
  arr.add(value);
}

void detaBaseESP8266::UpdatePrepend(const char* key, const char* value) {
  JsonArray arr = doc["prepend"][key].to<JsonArray>();
  arr.add(value);
}

void detaBaseESP8266::UpdateDelete(const char* key) {
  doc["delete"].add(key);
}

bool detaBaseESP8266::sendUpdate(const String& key) {
  // Build the URL for the update
  String url = "https://database.deta.sh/v1/" + String(projectId) + "/" + String(baseName) + "/items/" + key;

  // Serialize the JSON payload to a string
  String payload;
  serializeJson(doc, payload);

  // Initialize the HTTP client and set headers
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", String(apiKey));

  // Send the PATCH request with the JSON payload
  int httpResponseCode = http.PATCH(payload);

  // Store the response code and payload
  lastResponseCode = httpResponseCode;
  responsePayload = http.getString();

  // Check the response code
  doc.clear();
  return httpResponseCode >= 200 && httpResponseCode < 300;
}

bool detaBaseESP8266::sendData() {
  // Build the URL for the base
  String url = "https://database.deta.sh/v1/" + String(projectId) + "/" + String(baseName) + "/items";

  // Serialize the JSON payload to a string
  String payload;
  serializeJson(doc, payload);

  // Initialize the HTTP client and set headers
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", String(apiKey));

  // Send the PUT request with the JSON payload
  int httpResponseCode = http.PUT(payload);

  // Store the response code and payload
  lastResponseCode = httpResponseCode;
  responsePayload = http.getString();

  // Check the response code
  doc.clear();
  return httpResponseCode >= 200 && httpResponseCode < 300;
}

void detaBaseESP8266::getItem(const String& key) {
  // Build the URL for the specific item
  String url = "https://database.deta.sh/v1/" + String(projectId) + "/" + String(baseName) + "/items/" + key;

  // Initialize the HTTP client and set headers
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", String(apiKey));

  // Send the GET request
  int httpResponseCode = http.GET();

  // Store the response code and payload
  lastResponseCode = httpResponseCode;
  responsePayload = http.getString();

  doc.clear();
}

bool detaBaseESP8266::deleteItem(const String& key) {
  // Build the URL for the specific item
  String url = "https://database.deta.sh/v1/" + String(projectId) + "/" + String(baseName) + "/items/" + key;

  // Initialize the HTTP client and set headers
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-Key", String(apiKey));

  // Send the DELETE request
  int httpResponseCode = http.sendRequest("DELETE");

  // Store the response code and payload
  lastResponseCode = httpResponseCode;
  responsePayload = http.getString();

  // Check the response code
  doc.clear();
  return httpResponseCode >= 200 && httpResponseCode < 300;
}

String detaBaseESP8266::getData(const char* key) {
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, responsePayload);
  return doc[key].as<String>();
}

int detaBaseESP8266::getIntData(const char* key) {
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, responsePayload);
  return doc[key].as<int>();
}

float detaBaseESP8266::getFloatData(const char* key) {
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, responsePayload);
  return doc[key].as<float>();
}

bool detaBaseESP8266::getBoolData(const char* key) {
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, responsePayload);
  return doc[key].as<String>() == "true";
}
