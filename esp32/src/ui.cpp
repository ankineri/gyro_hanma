#include <algorithm>

#include "ui.h"
#include "ui/ui.h"
void Ui::set_gear_state(GearState gear_state)
{
    lv_obj_add_flag(ui_imgForward, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgReverse, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_imgFaster, LV_OBJ_FLAG_HIDDEN);
    switch (gear_state)
    {
    case GearState::FORWARD:
        lv_obj_clear_flag(ui_imgForward, LV_OBJ_FLAG_HIDDEN);
        break;
    case GearState::REVERSE:
        lv_obj_clear_flag(ui_imgReverse, LV_OBJ_FLAG_HIDDEN);
        break;
    case GearState::FASTER:
        lv_obj_clear_flag(ui_imgFaster, LV_OBJ_FLAG_HIDDEN);
        break;
    }
}

void Ui::set_pedal_state(bool pedal_state)
{

        lv_obj_set_style_bg_color(ui_lblGo, pedal_state ? lv_color_hex(0x00FF00) : lv_color_hex(0xBEBEBE), LV_PART_MAIN | LV_STATE_DEFAULT);

}


void Ui::error(std::string message)
{
    lv_label_set_text(ui_lblError, message.c_str());
    lv_disp_load_scr(ui_Screen2);
}

void Ui::set_battery_voltage(float voltage)
{
    char buffer[10];
    snprintf(buffer, 10, "%.1fV", voltage);
    lv_label_set_text(ui_lblBattery, buffer);
    lv_arc_set_value(ui_arcBattery, std::max(0, std::min(420, static_cast<int>(voltage * 10)))); // Use std::max instead of max
}
