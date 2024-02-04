// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblTitle = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_lblTitle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblTitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblTitle, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_lblTitle, "Hanma");
    lv_obj_set_style_text_color(ui_lblTitle, lv_color_hex(0xA97C00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lblTitle, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_arcBattery = lv_arc_create(ui_Screen1);
    lv_obj_set_width(ui_arcBattery, 70);
    lv_obj_set_height(ui_arcBattery, 70);
    lv_obj_set_align(ui_arcBattery, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_clear_flag(ui_arcBattery, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);      /// Flags


    ui_lblBattery = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_lblBattery, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblBattery, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblBattery, 125);
    lv_obj_set_y(ui_lblBattery, 84);
    lv_obj_set_align(ui_lblBattery, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblBattery, "0v");

}