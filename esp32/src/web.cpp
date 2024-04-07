#include "web.h"
static void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

WebServer::WebServer(ConfigurableParams &params, std::function<void()> on_change) : params(params), on_change(on_change), server(80)
{
}

void WebServer::setup_web()
{
    if (SPIFFS.begin(true))
    {
        Serial.println("SPIFFS mounted successfully.");
    }
    else
    {
        Serial.println("SPIFFS mount failed. Check your filesystem.");
    }
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
    server.on("/save_settings", HTTP_POST, [this](AsyncWebServerRequest *request)
              {
        bool ok = true;
        auto new_params = params;
        if (!request->hasParam("spd_coef", true) || !request->hasParam("spd_fast", true) || !request->hasParam("spd_fwd", true) || !request->hasParam("spd_back", true) || !request->hasParam("acc_fwd", true) || !request->hasParam("acc_back", true) || !request->hasParam("acc_slwdn", true)) {
            request->send(400, "text/plain", "Bad request");
            return;
        }
        ok = sscanf(request->getParam("spd_coef", true)->value().c_str(), "%f", &new_params.spd_coef) == 1;
        ok &= sscanf(request->getParam("spd_fast", true)->value().c_str(), "%d", &new_params.spd_fast) == 1;
        ok &= sscanf(request->getParam("spd_fwd", true)->value().c_str(), "%d", &new_params.spd_fwd) == 1;
        ok &= sscanf(request->getParam("spd_back", true)->value().c_str(), "%d", &new_params.spd_back) == 1;

        ok &= sscanf(request->getParam("acc_fwd", true)->value().c_str(), "%d", &new_params.acc_fwd) == 1;
        ok &= sscanf(request->getParam("acc_back", true)->value().c_str(), "%d", &new_params.acc_back) == 1;
        ok &= sscanf(request->getParam("acc_slwdn", true)->value().c_str(), "%d", &new_params.acc_slwdn) == 1;

        if (ok) {
            params = new_params;
            on_change();
            request->send(200, "text/plain", "OK");
        } else {
            request->send(400, "text/plain", "Bad request");
        } });

    server.on("/get_settings", HTTP_GET, [this](AsyncWebServerRequest *request)
              {
        char json[256];
        snprintf(json, sizeof(json), "{\"spd_coef\":%f,\"spd_fast\":%d,\"spd_fwd\":%d,\"spd_back\":%d,\"acc_fwd\":%d,\"acc_back\":%d,\"acc_slwdn\":%d}",
                 params.spd_coef, params.spd_fast, params.spd_fwd, params.spd_back, params.acc_fwd, params.acc_back, params.acc_slwdn);
        request->send(200, "application/json", json); });

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.onNotFound(notFound);

    server.begin();
}
