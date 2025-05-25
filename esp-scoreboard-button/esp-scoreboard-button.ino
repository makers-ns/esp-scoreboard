/**
   Based on BasicHTTPClient.ino

*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ButtonDebounce.h>

ESP8266WiFiMulti WiFiMulti;

// If you don't have ../wifi_parameters.h make sure to crete one.
// const char* ssid = "SSID";
// const char* password = "WIFIpassword";
#include "wifi_parameters.h"

ButtonDebounce button(D3, 250); // Flash button

int doHTTP(const char* option) {  // <-- changed from char* to const char*

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    char url[200];

    Serial.print("[HTTP] begin...\n");

    sprintf(url, "http://192.168.4.1/&action=%s/&n", option);
    if (http.begin(client, url)) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();

    } else {
      Serial.printf("[HTTP} Unable to connect\n");
      return 0;
    }
    return 1;
  }
  return 0;
}

void buttonCallback(int state) {
  if(state == 0)
  {
    doHTTP("1"); // Left player
    // for testing both
    //delay(3000); 
    //doHTTP("3"); // Ritht player
  }
}

void setup() {

  Serial.begin(38400);

  button.setCallback(buttonCallback);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  while(!doHTTP("2")) // reset score
  {
    Serial.print(".");
    delay(500);
  }
}

void loop() {
  button.update();
}
