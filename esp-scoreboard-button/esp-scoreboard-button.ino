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

int doHTTP(char* option) {

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    char url[200];

    Serial.print("[HTTP] begin...\n");

    sprintf(url, "http://192.168.4.1/&action=%s/&n", option);
    if (http.begin(client, url)) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        //if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          //String payload = http.getString();
          //Serial.println(payload);
        //}
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

  Serial.begin(115200);

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
