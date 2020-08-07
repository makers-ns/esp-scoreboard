# esp-scoreboard
This is a wireless scoreboard based on esp8266/esp32. It can be used for various sports and games.

Make sure you create wifi_parameters.h in /esp-scoreboard/

```
#ifndef ESP_SB_WIFI_PARAMS
#define ESP_SB_WIFI_PARAMS
//WiFi login parameters - network name and password

const char* ssid = "SSID";
const char* password = "pass";

#endif
```
