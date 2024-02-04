#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include <Audio.h>
#include <Wire.h>
#include <vector>

#include "led.h"
#include "task.h"
#include "hanma.h"
#include "buttons.h"


#define WIFI_SSID "Hanma-AP"
#define WIFI_PASSWORD "2Y-LYBQzeipA"

vector<Task *> tasks;

Hanma hanma;
Led led;
Buttons buttons;

void OnButtonClicked(lv_event_t *e)
{
    // static uint8_t cnt = 0;
    // cnt++;
    // lv_label_set_text_fmt(ui_lblCountValue, "%d", cnt);
    // speed = 40 + speed;
    // if (speed > 16 * 40)
    //     speed = 0;
}

void setup()
{
    tasks.push_back(&hanma);
    tasks.push_back(&led);
    tasks.push_back(&buttons);
    // delay(250);
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    log_i("Free heap: %d bytes", ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    log_i("SDK version: %s", ESP.getSdkVersion());

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);

    // #ifdef BOARD_HAS_SPEAK
    //     // Connect to WiFi
    //     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    //     if (WiFi.waitForConnectResult() == WL_CONNECTED)
    //     {
    //         audio = new Audio(true, I2S_DAC_CHANNEL_LEFT_EN);
    //         audio->forceMono(true);
    //         audio->setVolume(10);

    //         while (!audio->connecttohost(RADIO_URL))
    //             delay(500);
    //     }
    // #endif

    smartdisplay_init();

    auto disp = lv_disp_get_default();
    ui_init();
    for (auto task : tasks)
    {
        task->setup();
    }
}


Led led;

void loop()
{
    led.update_speed(hanma.get_speed());
    for (auto task : tasks)
    {
        task->step();
    }
    lv_timer_handler();
}