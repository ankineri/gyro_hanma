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
#include "ui.h"
#include "gear_state.h"
#include "consts.h"
#include "web.h"

#define WIFI_SSID "Hanma-AP"
#define WIFI_PASSWORD "2Y-LYBQzeipA"

vector<Task *> tasks;

ConfigurableParams params;

Hanma hanma;
Led led;
Buttons buttons;
Ui ui;
WebServer web(params, []() {
    // ui.update();
});

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
    params.spd_fwd = NORMAL_SPEED;
    params.spd_back = REVERSE_SPEED;
    params.spd_fast = FAST_SPEED;
    params.acc_fwd = NORMAL_ACCELERATION;
    params.acc_back = NORMAL_ACCELERATION;
    params.acc_slwdn = FAST_ACCELERATION;

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

    web.setup_web();

    // WiFi.mode(WIFI_AP);
    // WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
    // WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);

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
    lv_disp_set_rotation(disp, LV_DISP_ROT_270);
    ui_init();
    for (auto task : tasks)
    {
        task->setup();
    }
}
unsigned long last_updated_gear = 0;
int i = 0;
bool error = false;

void trigger_error(const char *message)
{
    ui.error(message);
    error = true;
    led.error();
}

void loop()
{
    if (millis() < 200) {
        return;
    }
    lv_timer_handler();

    if (error) {
        return;
    }

    for (auto task : tasks)
    {
        task->step();
    }

    ui.set_gear_state(buttons.get_gear_state());
    ui.set_pedal_state(buttons.is_pedal_pressed());
    ui.set_battery_voltage(hanma.get_battery_voltage());
    led.update_speed(hanma.get_speed());

    hanma.set_acceleration(NORMAL_ACCELERATION);

    if (!buttons.is_pedal_pressed())
    {
        hanma.set_speed(0);
        hanma.set_acceleration(params.acc_slwdn);
    } else {
        if (buttons.get_gear_state() == GearState::FORWARD)
        {
            hanma.set_speed(params.spd_fwd * params.spd_coef);
            hanma.set_acceleration(params.acc_fwd);
        } else if (buttons.get_gear_state() == GearState::FASTER)
        {
            hanma.set_speed(params.spd_fast * params.spd_coef);
            hanma.set_acceleration(params.acc_fwd);
        }
        else if (buttons.get_gear_state() == GearState::REVERSE)
        {
            hanma.set_speed(params.spd_back * params.spd_coef);
            hanma.set_acceleration(params.acc_back);
        }
    }


    if (buttons.get_gear_state() == GearState::ERROR)
    {
        trigger_error("Error reading gear state.\nTalk to ankineri@.");
        return;
    }

    if (hanma.get_voltages_age() > 10000)
    {
        trigger_error("Voltage read timeout.\nTalk to ankineri@.");
        return;
    }

    Serial.print("Battery voltage: ");
    Serial.println(hanma.get_battery_voltage());
    Serial.print("Charger voltage: ");
    Serial.println(hanma.get_charger_voltage());

    if (hanma.get_charger_voltage() > 10) {
        trigger_error("Charger connected.\nPlease turn off the key.");
        return;
    }

    if (hanma.get_battery_voltage() < 28 && hanma.get_battery_voltage() > 5)
    {
        trigger_error("Battery voltage too low.\nPlease charge the battery.");
        return;
    }

}