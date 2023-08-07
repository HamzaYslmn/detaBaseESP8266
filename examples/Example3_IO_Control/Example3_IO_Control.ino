/*
| Label | GPIO  | Input        | Output     | Notes                                 |
|-------|-------|--------------|------------|---------------------------------------|
| D0    | GPIO16| no interrupt | no PWM     | HIGH at boot, used to wake from deep sleep 
| D1    | GPIO5 | OK           | OK         | Often used as SCL (I2C)               
| D2    | GPIO4 | OK           | OK         | Often used as SDA (I2C)               
| D3    | GPIO0 | pulled up    | OK         | Connected to FLASH button, boot fails if pulled LOW |
| D4    | GPIO2 | pulled up    | OK         | HIGH at boot, connected to on-board LED, boot fails if pulled LOW 
| D5    | GPIO14| OK           | OK         | SPI (SCLK)                            
| D6    | GPIO12| OK           | OK         | SPI (MISO)                            
| D7    | GPIO13| OK           | OK         | SPI (MOSI)                            
| D8    | GPIO15| pulled to GND| OK         | SPI (CS), Boot fails if pulled HIGH   
| RX    | GPIO3 | OK           | RX pin     | HIGH at boot                          
| TX    | GPIO1 | TX pin       | OK         | HIGH at boot, debug output at boot, boot fails if pulled LOW 
| A0    | ADC0  | Analog Input | X          | Analog input                                             
*/

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <detaBaseArduinoESP8266.h>
#include "certs.h"

const char* detaKey = "a0uhqqxxxx_xxxxxxxxxxxxxxxxxxxxxxxx";
const char* detaID = "a0uhqqxxxxx";
const char* detaBaseName = "LOG";
const char* ssid = "SSID";
const char* password = "PASSWORD";

unsigned long previousMillis = 0;
const long interval = 4000; // 4 seconds

detaBaseArduinoESP8266 detabase(detaKey, detaID, detaBaseName);
X509List cert(cert_DigiCert_Global_Root_CA);

bool onboardled;
int integer = 0;

String entryKey2 = "Esp8266 Output";

//Outputs

bool D1Value = LOW;
bool D2Value = LOW;
bool D3Value = LOW;
bool LEDValue = LOW;
bool D8Value = LOW;

//esp8266 restart
bool reset = false;


String entryKey1 = "Esp8266 Input";
//Inputs
bool D5Value = LOW;
bool D6Value = LOW;
bool D7Value = LOW;
int A0Value = 0;

//PUT request


void sendDetaSpaceInput() {
  detabase.addData("key", entryKey1);
  detabase.addData("D5", D5Value);
  detabase.addData("D6", D6Value);
  detabase.addData("D7", D7Value);
  detabase.addData("A0", A0Value);

  detabase.addData("0RESET", "RESTART");

  bool success = detabase.sendData(); // send

  if (success) {
    Serial.println("Output Data added successfully!");
  } else {
    Serial.println("Failed to add Output data!");
  }
}

void sendDetaSpaceOutput() {
  detabase.addData("key", entryKey2);
  detabase.addData("D1", D1Value);
  detabase.addData("D2", D2Value);
  detabase.addData("D3", D3Value);
  detabase.addData("D8", D8Value);
  detabase.addData("onLED", LEDValue);

  detabase.addData("0RESET", reset);

  bool success = detabase.sendData(); // send

  if (success) {
    Serial.println("Input Data added successfully!");
  } else {
    Serial.println("Failed to add Input data!");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  
  
  pinMode(5 ,OUTPUT); // D1
  pinMode(4 ,OUTPUT); // D2
  pinMode(0 ,OUTPUT); // D3
  pinMode(15,OUTPUT); // D8

  pinMode(A0,INPUT); // A0
  pinMode(14,INPUT); // D5
  pinMode(12,INPUT); // D6
  pinMode(13,INPUT); // D7

  //RX
  pinMode(3,INPUT); // RX
  Serial.println("RX ="+String(digitalRead(3)));
  

  
  configTime(3*3600, 0, "pool.ntp.org"); // For SSL, UTC+3 Turkey
  WiFiClientSecure client;
  client.setTrustAnchors(&cert);

  delay(100);

  digitalWrite(LED_BUILTIN, LOW); // Onboard LED ON
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }
  Serial.println("Connection Done");
  digitalWrite(LED_BUILTIN, HIGH); // Onboard LED OFF

  //Send First Customizations
  sendDetaSpaceInput();
  delay(1000);
  sendDetaSpaceOutput();
}

void loop() {
  unsigned long currentMillis = millis();

  // Call the functions every 3 seconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    GetDetaSpace();
    UpdateDetaSpace();
  };
  
  delay(1000);
}

//Void Get Output Pins
void GetDetaSpace() {
  detabase.getItem(entryKey2);

  reset = detabase.getBoolData("0RESET");
  Serial.print("Reset = ");
  Serial.println(reset);

  if (reset) {
    Serial.println("Resetting...");
    ESP.restart();
  }
  
  D1Value = detabase.getBoolData("D1");
  D2Value = detabase.getBoolData("D2");
  D3Value = detabase.getBoolData("D3");
  D8Value = detabase.getBoolData("D8");
  LEDValue = detabase.getBoolData("onLED");

  Serial.println("Output Pins...");

  Serial.println("D1 = " + String(D1Value));
  digitalWrite(5, D1Value);

  Serial.println("D2 = " + String(D2Value));
  digitalWrite(4, D2Value);

  Serial.println("D3 = " + String(D3Value));
  digitalWrite(0, D3Value);

  Serial.println("D8 = " + String(D8Value));
  digitalWrite(15, D8Value);

  Serial.println("onLED = " + String(LEDValue));
  digitalWrite(2, LEDValue);  
}

//Void Update Input Pins
void UpdateDetaSpace() {

  Serial.println("\nInput Pins...");
    
  // print the readings in the Serial Monitor
  D5Value = digitalRead(14);
  Serial.println("D5 = " + String(D5Value));

  D6Value = digitalRead(12);
  Serial.println("D6 = " + String(D6Value));

  D7Value = digitalRead(13);
  Serial.println("D7 = " + String(D7Value));

  A0Value = analogRead(A0);
  Serial.println("A0 = " + String(A0Value));

  detabase.UpdateSet("D5", D5Value);
  detabase.UpdateSet("D6", D6Value);
  detabase.UpdateSet("D7", D7Value);
  detabase.UpdateSet("A0", A0Value);

  bool success = detabase.sendUpdate(entryKey1); // send

  if (success) {
    Serial.println("Data Updated successfully!");
  } else {
    Serial.println("Failed to add data!");
  }
}