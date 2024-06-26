// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "ERROR");
    lv_obj_set_style_text_font(ui_Label3, &ui_font_px76, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblError = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_lblError, lv_pct(100));
    lv_obj_set_height(ui_lblError, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblError, 0);
    lv_obj_set_y(ui_lblError, 66);
    lv_obj_set_align(ui_lblError, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblError, "Unknown error");
    lv_obj_set_style_text_align(ui_lblError, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lblError, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

}
