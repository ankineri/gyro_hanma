#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include "consts.h"

#include <functional>
struct ConfigurableParams {
    float spd_coef;
    int16_t spd_fast;
    int16_t spd_fwd;
    int16_t spd_back;
    int16_t acc_fwd;
    int16_t acc_back;
    int16_t acc_slwdn;
};
class WebServer {
    private:
    ConfigurableParams &params;
    std::function<void()> on_change;
    AsyncWebServer server;
public:
    WebServer(ConfigurableParams &params, std::function<void()> on_change);
    void setup_web();
};
